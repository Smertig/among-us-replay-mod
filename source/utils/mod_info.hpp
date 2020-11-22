#pragma once

#include <string_view>

enum class game_version {
    v2020_6_9s,
    v2020_9_22s,
    v2020_10_8i,
    v2020_10_22s,
    v2020_11_4s
};

namespace mod_info {

constexpr std::string_view name    = "Replay Mod";
constexpr std::string_view version = "0.6.2";

game_version get_game_version();

} // namespace mod_info
