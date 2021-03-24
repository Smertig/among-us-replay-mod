#pragma once

#include <autogen/UnityEngine/MonoBehaviour.hpp>
#include <autogen/TaskTypes.hpp>
#include <autogen/SystemTypes.hpp>

struct PlayerControl;

// MCOJPKFLEIL in 2020.10.8i
// LOBBAHDOFGE in 2020.10.22s
// FKAPFNAKPBG in 2020.11.4s
// CLCMPFJIIEN in 2020.11.17s
// PILBGHDHJLH in 2020.12.9s
// PlayerTask in 2021.3.5s
struct PlayerTask : UnityEngine::MonoBehaviour {
    std::int32_t _Index;
    std::uint32_t _Id;
    PlayerControl* _Owner;
    SystemTypes StartAt; // [marker]
    TaskTypes TaskType;
    struct Minigame_o *MinigamePrefab;
    bool HasLocation;
    bool LocationDirty;
};
CHECK_TYPE(PlayerTask, 0x20);
