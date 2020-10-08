#pragma once

#include <cstdint>

namespace InnerNet {

// CCCPFILPMBO since 2020.9.22
enum class GameStates : std::uint8_t {
    NotStarted = 0,
    Started = 1,
    Ended = 2,
    Destroyed = 3,
};

} // namespace InnerNet
