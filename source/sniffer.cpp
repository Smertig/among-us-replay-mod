#include <fmt/format.h>
#include <magic_enum.hpp>

#include "utils/hook.hpp"
#include "utils/enums.hpp"
#include "utils/utils.hpp"
#include "utils/mod_info.hpp"
#include "utils/binary_serializer.hpp"

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
        const auto game_version = UnityEngine::Application::get_version();
        if (game_version != mod_info::compatible_game_version) {
            const auto msg = fmt::format("{} was built for Amons Us v{}.\nYour game version is v{}.\n\nIt may not work as expected.",
                                         mod_info::name,
                                         mod_info::compatible_game_version,
                                         game_version
                                         );

            utils::msgbox_warning(msg);
        }

        instance();
    }

    void start() {
        if (is_started()) {
            // TODO: log
            stop();
        }

        const std::filesystem::path REPLAY_DIR = "./replay";

        std::filesystem::create_directories(REPLAY_DIR);
        auto filename = REPLAY_DIR / fmt::format("replay_{}.aurp", utils::get_date_string(std::chrono::system_clock::now()));
        m_stream = std::fstream(filename, std::fstream::out | std::fstream::binary);

        fmt::print("Start recording..\n");
    }

    void stop() {
        m_stream = std::fstream{};

        fmt::print("Stop recording..\n");
    }

    bool is_started() {
        return !!m_stream;
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

    void on_frame(const GameData* game) {
        for (const auto& player : *game->AllPlayers) {
            if (!player->_object) {
                return;
            }
        }

        std::map<std::uint8_t, player_state> current_player_states;
        for (const auto& player : *game->AllPlayers) {
            current_player_states.emplace(player->PlayerId, player_state(*player));
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
    }

private:
    static replay_tracer& instance() {
        static replay_tracer instance_;
        return instance_;
    }

    explicit replay_tracer() {
        init_hooks();
    }

    void init_hooks() {
        hook_method<void(*)(void*)>("InnerNet", "InnerNetClient", "Update", [this](auto original, auto self) {
            original(self);

            auto game = GameData::instance();
            if (!game) return;

            const auto game_state = AmongUsClient::Instance()->GameState;
            if (game_state == AmongUsClient::GameStates::NotJoined || game_state == AmongUsClient::GameStates::Ended && this->is_started()) {
                this->stop();
            }

            if (this->is_started()) {
                this->on_frame(game);
            }
        });

        hook_method<void(*)(ShipStatus*)>("ShipStatus", "Begin", [this](auto original, ShipStatus* self) {
            original(self);

            this->try_start_round();
        });

        hook_method<void(*)(PlayerControl*, void*)>("PlayerControl", "SetTasks", [this](auto original, auto... args) {
            original(args...);

            for (const auto& player : *GameData::instance()->AllPlayers) {
                if (!player->Tasks || player->Tasks->size() == 0) {
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
    replay_tracer::init();
}
