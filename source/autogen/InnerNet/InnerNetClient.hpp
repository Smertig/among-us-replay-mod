#pragma once

#include <autogen/UnityEngine/MonoBehaviour.hpp>

namespace InnerNet {

// PJBHKAHJEMG in 2020.10.8i
// DNAFMCDBMCI in 2020.10.22s
// DBDDAJAICFN in 2020.11.4s
// FMJPJKCNIKM in 2020.11.17s
// KHNHJFFECBP in 2020.12.9s
// InnerNetClient in 2021.3.5s
// InnerNetClient in 2021.4.12s
struct InnerNetClient : UnityEngine::MonoBehaviour {
    // InnerNetClient.IFLBIJFJPMK in 2020.9.22
    // PJBHKAHJEMG.KDKPEGOCIJA in 2020.10.8i
    // DNAFMCDBMCI.JPCEFDHGHAK in 2020.10.22s
    // DBDDAJAICFN.DKEKFCCGGEO in 2020.11.4s
    // FMJPJKCNIKM.ONHEJJJIKDI in 2020.11.17s
    // KHNHJFFECBP.KGEKNMMAKKN in 2020.12.9s
    // InnerNetClient.CGJDIIGHLGC in 2021.3.5s
    enum class GameStates : std::int32_t {
        NotJoined = 0, // [marker]
        Joined = 1,
        Started = 2,
        Ended = 3,
    };

    float MinSendInterval; // [marker]
    std::uint32_t NetIdCnt;
    float timer;
    struct UnityEngine_AddressableAssets_AssetReference_array* SpawnableObjects; // type changed in 2021.3.5s
    struct UnityEngine_InnerNetObject_array* NonAddressableSpawnableObjects; // since 2021.3.5s; UnityEngine_GameObject_array until 2021.4.12s
    bool InOnlineScene;
    struct System_Collections_Generic_HashSet_uint__o* DestroyedObjects;
    struct System_Collections_Generic_List_InnerNetObject__o* allObjects;
    struct System_Collections_Generic_Dictionary_uint__InnerNetObject__o* allObjectsFast;
    struct Hazel_MessageWriter_array* Streams;
    std::int32_t ODDLPKAHFCG; // since 2021.3.5s
    struct System_String_o* networkAddress;
    std::int32_t networkPort;
    struct Hazel_Udp_UnityUdpClientConnection_o* connection;
    std::int32_t mode;
    std::int32_t GameMode; // [enum] since 2021.4.12s
    std::int32_t GameId;
    std::int32_t HostId;
    std::int32_t ClientId;
    struct System_Collections_Generic_List_ClientData__o* allClients;
    std::int32_t LastDisconnectReason;
    struct System_String_o* LastCustomDisconnect;
    struct System_Collections_Generic_List_Action__o* PreSpawnDispatcher;
    struct System_Collections_Generic_List_Action__o* Dispatcher;
    bool _IsGamePublic_k__BackingField;
    GameStates GameState;
    struct System_Collections_Generic_List_Action__o *TempQueue;
    bool appPaused;

    static Class<InnerNetClient>* get_class() {
        switch (mod_info::get_game_version()) {
            case game_version::v2020_6_9s:   return Class<InnerNetClient>::find("InnerNet", "InnerNetClient");
            case game_version::v2020_9_22s:  return Class<InnerNetClient>::find("InnerNet", "InnerNetClient");
            case game_version::v2020_10_8i:  return Class<InnerNetClient>::find("PJBHKAHJEMG");
            case game_version::v2020_10_22s: return Class<InnerNetClient>::find("DNAFMCDBMCI");
            case game_version::v2020_11_4s:  return Class<InnerNetClient>::find("DBDDAJAICFN");
            case game_version::v2020_11_17s: return Class<InnerNetClient>::find("FMJPJKCNIKM");
            case game_version::v2020_12_9s:  return Class<InnerNetClient>::find("KHNHJFFECBP");
            case game_version::v2021_3_5s:   return Class<InnerNetClient>::find("InnerNet", "InnerNetClient");
            case game_version::v2021_4_12s:  return Class<InnerNetClient>::find("InnerNet", "InnerNetClient");
        }
        return nullptr;
    }

    // No [marker], name shouldn't change
    void Update();
};
CHECK_TYPE(InnerNetClient, 0x74);

} // namespace InnerNet

template <>
const char* get_method_name<&InnerNet::InnerNetClient::Update>() {
    switch (mod_info::get_game_version()) {
        case game_version::v2020_6_9s:   return "Update";
        case game_version::v2020_9_22s:  return "Update";
        case game_version::v2020_10_8i:  return "Update";
        case game_version::v2020_10_22s: return "Update";
        case game_version::v2020_11_4s:  return "Update";
        case game_version::v2020_11_17s: return "Update";
        case game_version::v2020_12_9s:  return "Update";
        case game_version::v2021_3_5s:   return "Update";
        case game_version::v2021_4_12s:  return "Update";
    }
    return nullptr;
}
