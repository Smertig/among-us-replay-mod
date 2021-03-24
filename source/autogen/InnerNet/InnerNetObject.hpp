#pragma once

#include <autogen/UnityEngine/MonoBehaviour.hpp>

namespace InnerNet {

// OMAONGEPDJH in 2020.10.8i
// PEIOEODMCCN in 2020.10.22s
// MILGAMDLABC in 2020.11.4s
// JBBAENBKONG in 2020.11.17s
// NJAHILONGKN in 2020.12.9s
// InnerNetObject in 2021.3.5s
struct InnerNetObject : UnityEngine::MonoBehaviour {
    std::uint32_t SpawnId; // [marker]
    std::uint32_t NetId;
    std::uint32_t DirtyBits;
    std::uint8_t SpawnFlags;
    std::uint8_t sendMode;
    std::int32_t OwnerId;
    bool DespawnOnDestroy;
};
CHECK_TYPE(InnerNetObject, 0x1C);

} // namespace InnerNet
