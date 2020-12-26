#pragma once

#include <string_view>

enum class game_version {
    v2020_6_9s,
    v2020_9_22s,
    v2020_10_8i,
    v2020_10_22s,
    v2020_11_4s,
    v2020_11_17s,
    v2020_12_9s
};

namespace mod_info {

constexpr std::string_view name    = "Replay Mod";
constexpr std::string_view version = "0.6.5"; // do not forget about README!

game_version get_game_version();

} // namespace mod_info
