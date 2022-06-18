#pragma once

#include <string_view>

enum class game_version {
    v2020_6_9s,
    v2020_9_22s,
    v2020_10_8i,
    v2020_10_22s,
    v2020_11_4s,
    v2020_11_17s,
    v2020_12_9s,
    v2021_3_5s,
    v2021_4_12s,
    v2022_3_29s,
    v2022_4_19s,
};

namespace mod_info {

constexpr std::string_view name    = "Replay Mod";
constexpr std::string_view version = "0.8.0"; // do not forget about README!

game_version get_game_version();

} // namespace mod_info
