#pragma once

#include <string_view>

struct game_version {
    std::uint16_t year;
    std::uint8_t month;
    std::uint8_t day;

    friend auto operator<=>(const game_version&, const game_version&) = default;

    std::string to_string() const;
};

namespace mod_info {

constexpr std::string_view mod_name    = "Replay Mod";
constexpr std::string_view mod_version = "0.9.0"; // do not forget about README!

constexpr auto min_supported_game_version = game_version{ .year = 2022, .month = 6, .day = 21 };
constexpr auto max_supported_game_version = game_version{ .year = 2022, .month = 7, .day = 12 };

game_version get_game_version();

bool validate_game_version();

} // namespace mod_info
