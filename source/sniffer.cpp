#include <fmt/format.h>
#include <magic_enum.hpp>
#include <spdlog/spdlog.h>

#include "utils/hook.hpp"
#include "utils/enums.hpp"
#include "utils/utils.hpp"
#include "utils/mod_info.hpp"
#include "utils/binary_serializer.hpp"
#include "utils/periodic_printer.hpp"
#include "utils/logger.hpp"

#include <autogen/PlayerControl.hpp>
#include <autogen/GameData.hpp>
#include <autogen/CustomNetworkTransform.hpp>
#include <autogen/AmongUsClient.hpp>
#include <autogen/UnityEngine/Application.hpp>
#include <autogen/ShipStatus.hpp>
#include <autogen/RoleBehaviour.hpp>
#include <autogen/InnerNet/ClientData.hpp>

#include <fstream>
#include <chrono>
#include <filesystem>
#include <map>
#include <ranges>
#include <set>

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

            ser.write(static_cast<std::uint8_t>(tasks.size()));
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

        spdlog::info("Start recording.. ({})", is_started());
    }

    void stop() {
        m_stream.close();
        m_start_time = {};
        m_players.clear();
        m_ignored_players.clear();

        spdlog::info("Stop recording.. ({})", is_started());
    }

    bool is_started() const {
        return m_stream.is_open();
    }

    void try_stop_round() {
        if (is_started()) {
            stop();
        }
    }

    void try_start_round() {
        if (!is_started()) {
            start();
            on_round_start(ShipStatus::instance(), GameData::instance());
        }
    }

    static std::int32_t get_map_id(const ShipStatus* ship) {
        static const std::map<std::string_view, std::int32_t> mapping = {
            { "ShipStatus",      0 },
            { "MiraShipStatus",  1 },
            { "PolusShipStatus", 2 },
            { "AirshipStatus",   3 },
        };

        const auto ship_name = ship->get_class_name();

        const auto it = mapping.find(ship_name);
        if (it == mapping.end()) {
            spdlog::error("unknown ship status class: '{}'", ship_name);
            return -1;
        }

        return it->second;
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
        write(mod_info::mod_version);
        write(UnityEngine::Application::get_version());
        write(get_map_id(ship));

        const auto player_count = std::ranges::count_if(
            *game->AllPlayers,
            [](const auto player) { return !player->Disconnected; }
        );
        write(static_cast<std::uint32_t>(player_count));

        for (const auto player : *game->AllPlayers) {
            if (player->Disconnected) {
                spdlog::warn("Player {} disconnected before game starts", static_cast<int>(player->PlayerId));
                m_ignored_players.insert(player->PlayerId);
                continue;
            }

            const auto client_data = AmongUsClient::Instance()->GetClientFromCharacter(player->_object);
            assert(client_data);

            write(player->PlayerId);
            write(client_data->PlayerName);
            // TODO: update aurp version, remove casts, use strings
            write(static_cast<std::uint8_t>(client_data->ColorId)); // player->ColorId
            write(static_cast<std::uint32_t>(0)); // player->HatId is System::String now
            write(static_cast<std::uint32_t>(0)); // player->PetId is System::String now
            write(static_cast<std::uint32_t>(0)); // player->SkinId is System::String now
            write(player->Role->get_IsImpostor());
        }
    }

    bool is_player_valid(const GameData::PlayerInfo* player) const {
        return !is_null(player) &&
               !is_null(player->_object) &&
               !is_null(player->_object->NetTransform) &&
               !m_ignored_players.contains(player->PlayerId);
    }

    void on_frame(const GameData* game) {
        static periodic_printer printer("replay_tracer::on_frame", std::chrono::seconds(1));
        const auto print = printer.get_printer();

        print("game = {}, players = {}", fmt::ptr(game), fmt::ptr(game->AllPlayers));

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
        write(static_cast<std::uint8_t>(diff.size()));
        for (const auto& [id, state] : diff) {
            write(id, state);
        }

        m_players = std::move(current_player_states);

        print("diff is recorded ok, size {}", diff.size());
    }

    static replay_tracer& instance() {
        static replay_tracer instance_;
        return instance_;
    }

    explicit replay_tracer() {
        init_hooks();
    }

    void init_hooks() {
        ::hook_method<&InnerNet::InnerNetClient::Update>([this](auto original, InnerNet::InnerNetClient* self) {
            static periodic_printer printer("InnerNet::InnerNetClient::Update", std::chrono::seconds(1));
            const auto print = printer.get_printer();

            original(self);

            auto game = GameData::instance();
            if (is_null(game)) {
                print("GameData::instance() is null");
                return;
            }

            const auto game_state = AmongUsClient::Instance()->GameState;
            print("game state = {}, is_started = {}", game_state, is_started());

            if (game_state == AmongUsClient::GameStates::NotJoined || game_state == AmongUsClient::GameStates::Ended) {
                this->try_stop_round();
            }

            const bool should_be_started = [&]{
                // TODO: won't work in local games, because of GameStates::Joined
                if (game_state != AmongUsClient::GameStates::Started) {
                    return false;
                }

                if (is_null(GameData::instance()) || is_null(ShipStatus::instance())) {
                    return false;
                }

                for (const auto& player : *GameData::instance()->AllPlayers) {
                    if (player->Disconnected) {
                        continue;
                    }

                    if (is_null(player->Tasks) || player->Tasks->size() == 0) {
                        return false;
                    }

                    if (self->GetClientFromCharacter(player->_object) == nullptr) {
                        return false;
                    }
                }

                return true;
            }();

            if (should_be_started) {
                this->try_start_round();
            }

            if (this->is_started()) {
                this->on_frame(game);
            }
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
    std::set<std::uint8_t> m_ignored_players;
};

void enable_sniffer() {
    spdlog::set_level(spdlog::level::off);

    try {
        if (!mod_info::validate_game_version()) {
            return;
        }

        init_logger();
        replay_tracer::init();
    }
    catch (std::exception& e) {
        utils::msgbox_error(fmt::format(
            "Unhandled error during sniffer initialization: {}",
            e.what()
        ));
    }
}
