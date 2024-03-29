#pragma once

#include <autogen/UnityEngine/MonoBehaviour.hpp>

namespace InnerNet {

// il2cpp: struct InnerNet_InnerNetObject_Fields
struct InnerNetObject : UnityEngine::MonoBehaviour {
    std::uint32_t SpawnId;
    std::uint32_t NetId;
    std::uint32_t DirtyBits;
    std::uint8_t SpawnFlags;
    std::uint8_t sendMode;
    std::int32_t OwnerId;
    bool DespawnOnDestroy;
};
CHECK_TYPE(InnerNetObject, 0x1C);

} // namespace InnerNet
