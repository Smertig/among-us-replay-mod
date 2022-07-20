#include "mod_info.hpp"
#include "utils.hpp"

#include <autogen/UnityEngine/Application.hpp>

#include <fmt/format.h>

std::string game_version::to_string() const {
    return fmt::format("v{}.{}.{}", year, month, day);
}

namespace mod_info {

game_version get_game_version() {
    static const auto current_version = []{
        auto app_version = UnityEngine::Application::get_version();
        int year, month, day;
        if (sscanf_s(app_version.c_str(), "%d.%d.%d", &year, &month, &day) != 3) {
            throw std::runtime_error(fmt::format("can't parse game version from {}", app_version));
        }

        return game_version{
            .year = static_cast<std::uint16_t>(year),
            .month = static_cast<std::uint8_t>(month),
            .day = static_cast<std::uint8_t>(day)
        };
    }();

    return current_version;
}

bool validate_game_version() {
    constexpr auto GITHUB_REFERENCE = "https://github.com/Smertig/among-us-replay-mod/releases";

    const auto current_game_version = get_game_version();
    if (current_game_version < min_supported_game_version) {
        utils::msgbox_error(fmt::format(
            "{} v{} doesn't support Among Us {} (min supported version is {}).\n"
            "\n"
            "Your game version is too old, please use older mod version or update the game.\n"
            "\n"
            "All mod versions can be found at {}",
            mod_name, mod_version,
            current_game_version.to_string(),
            min_supported_game_version.to_string(),
            GITHUB_REFERENCE
        ));
        return false;
    }

    if (current_game_version > max_supported_game_version) {
        const auto is_yes_pressed = utils::msgbox_warning_yesno(fmt::format(
            "Looks like Among Us was updated to {} but {} v{} doesn't know about that (latest known game version is {})\n"
            "\n"
            "1. You should download newer mod version at {}\n"
            "(please create an issue if there is no updated mod yet)\n"
            "\n"
            "OR\n"
            "\n"
            "2. Continue to use current mod version as is. It may lead to game CRASHES or incorrect replay capturing. You've been warned!\n"
            "\n"
            "Continue?",
            current_game_version.to_string(),
            mod_name,
            mod_version,
            max_supported_game_version.to_string(),
            GITHUB_REFERENCE
        ));

        if (!is_yes_pressed) {
            return false;
        }
    }

    return true;
}

} // namespace mod_info