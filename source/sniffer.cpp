#include <fmt/format.h>
#include <magic_enum.hpp>

#include "utils/hook.hpp"
#include "utils/enums.hpp"
#include "utils/utils.hpp"
#include "utils/mod_info.hpp"
#include "utils/binary_serializer.hpp"
#include "utils/periodic_printer.hpp"

#include <autogen/RpcCalls.hpp>
#include <autogen/PlayerControl.hpp>
#include <autogen/GameData.hpp>
#include <autogen/PlayerTask.hpp>
#include <autogen/CustomNetworkTransform.hpp>
#include <autogen/AmongUsClient.hpp>
#include <autogen/UnityEngine/Application.hpp>
#include <autogen/ShipStatus.hpp>

#include <fstream>
#include <chrono>
#include <filesystem>
#include <map>
#include <ranges>

template <>
struct fmt::formatter<UnityEngine::Vector2, char> : fmt::formatter<float> {
    auto format(const UnityEngine::Vector2& value, format_context& ctx) {
        return fmt::format_to(ctx.out(), "{{ {}, {} }}", value.x, value.y);
    }
};

class replay_tracer {
    enum class entry_type : std::uint8_t {
        frame_data = 0
    };

    struct player_state {
        struct task_state {
            bool is_complete;
            std::uint8_t type_id;
            std::uint32_t id;

            explicit task_state(const GameData::TaskInfo& info) {
                is_complete = info.Complete;
                type_id = info.TypeId;
                id = info.Id;
            }

            friend bool operator==(const task_state&, const task_state&) = default;

            void write_to(binary_serializer& ser) const {
                ser.write(is_complete);
                ser.write(type_id);
                ser.write(id);
            }
        };

        UnityEngine::Vector2 position;
        UnityEngine::Vector2 velocity;
        bool is_dead;
        bool is_disconnected;
        std::vector<task_state> tasks;

        friend bool operator==(const player_state&, const player_state&) = default;

        explicit player_state(const GameData::PlayerInfo& info) {
            auto body = info._object->NetTransform->body;

            position = body->get_position();
            velocity = body->get_velocity();
            is_dead = info.IsDead;
            is_disconnected = info.Disconnected;

            if (info.Tasks) {
                for (const auto &task : *info.Tasks) {
                    tasks.emplace_back(*task);
                }
            }
        }

        player_state(const player_state&) = default;

        void write_to(binary_serializer& ser) const {
            ser.write(position);
            ser.write(velocity);
            ser.write(is_dead);
            ser.write(is_disconnected);

            ser.write<std::uint8_t>(tasks.size());
            for (const auto& task : tasks) {
                ser.write(task);
            }
        }
    };

public:
    static void init() {
        instance();
    }

private:
    void start() {
        try_stop_round();

        const std::filesystem::path REPLAY_DIR = "./replay";

        std::filesystem::create_directories(REPLAY_DIR);
        auto filename = REPLAY_DIR / fmt::format("replay_{}.aurp", utils::get_date_string(std::chrono::system_clock::now()));
        m_stream.open(filename, std::fstream::out | std::fstream::binary);

        fmt::print("Start recording.. ({})\n", is_started());
    }

    void stop() {
        m_stream.close();

        fmt::print("Stop recording.. ({})\n", is_started());
    }

    bool is_started() {
        return m_stream.is_open();
    }

    void try_stop_round() {
        if (is_started()) {
            stop();
        }
    }

    void try_start_round() {
        fmt::print("try start round..\n");

        if (!is_started()) {
            start();
            on_round_start(ShipStatus::instance(), GameData::instance());
        }
    }

    void on_round_start(const ShipStatus* ship, const GameData* game) {
        if (!is_started()) {
            // TODO: log
            return;
        }

        m_start_time = now();

        write('A', 'U', 'R', 'P');
        write(DUMP_BINARY_VERSION);
        write(std::time(nullptr));
        write(mod_info::version);
        write(UnityEngine::Application::get_version());
        write(ship->Type);
        write(static_cast<std::uint32_t>(game->AllPlayers->size()));
        for (const auto player : *game->AllPlayers) {
            write(player->PlayerId);
            write(player->PlayerName);
            write(player->ColorId);
            write(player->HatId);
            write(player->PetId);
            write(player->SkinId);
            write(player->IsImpostor);
        }
    }

    static bool is_player_valid(const GameData::PlayerInfo* player) {
        return !is_null(player) &&
               !is_null(player->_object) &&
               !is_null(player->_object->NetTransform);
    }

    void on_frame(const GameData* game) {
        static periodic_printer printer("replay_tracer::on_frame", std::chrono::seconds(1));
        const auto print = printer.get_printer();

        print("game = {}, players = {}\n", fmt::ptr(game), fmt::ptr(game->AllPlayers));

        std::map<std::uint8_t, player_state> current_player_states;
        for (const auto& player : *game->AllPlayers) {
            if (is_player_valid(player)) {
                current_player_states.emplace(player->PlayerId, player_state(*player));
            }
        }

        // TODO: replace with std::views::keys
        bool need_refresh = !std::ranges::equal(
            m_players, current_player_states,
            {},
            &std::pair<const std::uint8_t, player_state>::first, &std::pair<const std::uint8_t, player_state>::first
        );

        // Calculate diff between previous and current state
        std::map<std::uint8_t, player_state> diff;
        if (need_refresh) {
            diff = current_player_states;
        }
        else {
            for (const auto& [id, current_state] : current_player_states) {
                auto old_state = m_players.at(id);
                if (old_state != current_state) {
                    diff.emplace(id, current_state);
                }
            }
        }

        // Dump state
        write_entry_header(entry_type::frame_data);
        write(need_refresh);
        write<std::uint8_t>(diff.size());
        for (const auto& [id, state] : diff) {
            write(id, state);
        }

        m_players = std::move(current_player_states);

        print("diff is recorded ok, size {}\n", diff.size());
    }

    static replay_tracer& instance() {
        static replay_tracer instance_;
        return instance_;
    }

    explicit replay_tracer() {
        init_hooks();
    }

    void init_hooks() {
        ::hook_method<&InnerNet::InnerNetClient::Update>([this](auto original, auto self) {
            static periodic_printer printer("InnerNet::InnerNetClient::Update", std::chrono::seconds(1));
            const auto print = printer.get_printer();

            original(self);

            auto game = GameData::instance();
            if (is_null(game)) {
                print("GameData::instance() is null\n");
                return;
            }

            const auto game_state = AmongUsClient::Instance()->GameState;
            print("game state = {}, is_started = {}\n", game_state, is_started());

            if (game_state == AmongUsClient::GameStates::NotJoined || game_state == AmongUsClient::GameStates::Ended) {
                this->try_stop_round();
            }

            if (this->is_started()) {
                this->on_frame(game);
            }
        });

        ::hook_method<&ShipStatus::Begin>([this](auto original, ShipStatus* self) {
            original(self);

            this->try_start_round();
        });

        ::hook_method<&PlayerControl::SetTasks>([this](auto original, auto... args) {
            original(args...);

            for (const auto& player : *GameData::instance()->AllPlayers) {
                if (player->Disconnected) {
                    continue;
                }

                if (is_null(player->Tasks) || player->Tasks->size() == 0) {
                    return;
                }
            }

            this->try_start_round();
        });
    }

    static std::chrono::system_clock::time_point now() {
        return std::chrono::system_clock::now();
    }

    void write_entry_header(entry_type type) {
        write(type);
        write_dt();
    }

    void write_dt() {
        using namespace std::chrono;

        const auto dt = static_cast<std::uint32_t>(duration_cast<milliseconds>(now() - m_start_time).count());

        write(dt);
    }

    template <class... Args>
    void write(const Args& ...args) {
        binary_serializer ser(m_stream);

        (ser.write(args), ...);
    }

    static inline constexpr std::uint32_t DUMP_BINARY_VERSION = 3;

    std::fstream m_stream;
    std::chrono::system_clock::time_point m_start_time;
    std::map<std::uint8_t, player_state> m_players;
};

void enable_sniffer() {
    try {
        mod_info::get_game_version();
    }
    catch (...) {
        const auto msg = fmt::format(
            "{} v{} doesn't support Among Us v{}.\n"
            "Try to download newer/older release from https://github.com/Smertig/among-us-replay-mod/releases",
            mod_info::name,
            mod_info::version,
            UnityEngine::Application::get_version()
        );

        utils::msgbox_warning(msg);
        return;
    }

    replay_tracer::init();
}
