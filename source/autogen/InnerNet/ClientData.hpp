#pragma once

#include <autogen/Object.hpp>

struct PlayerControl;

namespace InnerNet {

struct ClientData : ::Object {
    std::int32_t Id;
    bool InScene;
    bool IsReady;
    bool HasBeenReported;
    PlayerControl* Character;
    std::uint32_t PlayerLevel;
    struct PlatformSpecificData_o* PlatformData;
    System::String* PlayerName;
    System::String* ProductUserId;
    System::String* FriendCode;
    std::int32_t ColorId;
};
CHECK_TYPE(ClientData, 0x24);

}
