#include "mod_info.hpp"

#include <autogen/UnityEngine/Application.hpp>

#include <fmt/format.h>

#include <map>

namespace mod_info {

game_version get_game_version() {
    static const auto current_version = []{
        static const std::map<std::string_view, game_version> game_version_mapping {
            { "2020.6.9",   game_version::v2020_6_9s   },
            { "2020.9.22",  game_version::v2020_9_22s  },
            { "2020.10.8",  game_version::v2020_10_8i  },
            { "2020.10.22", game_version::v2020_10_22s },
            { "2020.11.4",  game_version::v2020_11_4s  },
            { "2020.11.17", game_version::v2020_11_17s },
            { "2020.12.9",  game_version::v2020_12_9s  },
            { "2021.3.5",   game_version::v2021_3_5s   },
        };

        static const std::map<game_version, std::string_view /* last supported mod version */> deprecated_versions {
            { game_version::v2020_6_9s,   "0.6.5" },
            { game_version::v2020_9_22s,  "0.6.5" },
            { game_version::v2020_10_8i,  "0.6.5" },
            { game_version::v2020_10_22s, "0.6.5" },
            { game_version::v2020_11_4s,  "0.6.5" },
            { game_version::v2020_11_17s, "0.6.5" },
            { game_version::v2020_12_9s,  "0.6.5" },
        };

        auto app_version = UnityEngine::Application::get_version();
        auto it = game_version_mapping.find(app_version);
        if (it == game_version_mapping.end()) {
            throw std::runtime_error(fmt::format("unknown game version: v{}", app_version));
        }

        const game_version current_game_version = it->second;

        if (auto it2 = deprecated_versions.find(current_game_version); it2 != deprecated_versions.end()) {
            throw std::runtime_error(fmt::format("game version v{} is too old, use v{} mod version or update the game", app_version, it2->second));
        }

        return current_game_version;
    }();

    return current_version;
}

} // namespace mod_info