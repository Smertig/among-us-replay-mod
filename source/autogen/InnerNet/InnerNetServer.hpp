#pragma once

#include <autogen/DestroyableSingleton.hpp>
#include <autogen/InnerNet/GameStates.hpp>

namespace InnerNet {

struct InnerNetServer : ::DestroyableSingleton<InnerNetServer> {
    std::int32_t HostId;
    struct System_Collections_Generic_HashSet_string__o* ipBans;
    std::int32_t Port;
    GameStates GameState;
    struct Hazel_Udp_UdpConnectionListener_o* listener;
    struct System_Collections_Generic_List_InnerNetServer_Player__o* Clients;

    static Class<InnerNetServer>* get_class() {
        return Class<InnerNetServer>::find("InnerNet", "InnerNetServer");
    }
};
CHECK_TYPE(InnerNetServer, 0x20);

} // namespace InnerNet
