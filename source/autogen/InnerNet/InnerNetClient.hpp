#pragma once

#include <autogen/UnityEngine/MonoBehaviour.hpp>

namespace InnerNet {

struct ClientData;
struct InnerNetObject;

// PJBHKAHJEMG in 2020.10.8i
// DNAFMCDBMCI in 2020.10.22s
// DBDDAJAICFN in 2020.11.4s
// FMJPJKCNIKM in 2020.11.17s
// KHNHJFFECBP in 2020.12.9s
// InnerNetClient since 2021.3.5s
struct InnerNetClient : UnityEngine::MonoBehaviour {
    // InnerNetClient.IFLBIJFJPMK in 2020.9.22
    // PJBHKAHJEMG.KDKPEGOCIJA in 2020.10.8i
    // DNAFMCDBMCI.JPCEFDHGHAK in 2020.10.22s
    // DBDDAJAICFN.DKEKFCCGGEO in 2020.11.4s
    // FMJPJKCNIKM.ONHEJJJIKDI in 2020.11.17s
    // KHNHJFFECBP.KGEKNMMAKKN in 2020.12.9s
    // InnerNetClient.CGJDIIGHLGC in 2021.3.5s
    // InnerNetClient.GameStates since 2022.3.29s
    enum class GameStates : std::int32_t {
        NotJoined = 0, // [marker]
        Joined = 1,
        Started = 2,
        Ended = 3,
    };

    float MinSendInterval;
    std::uint32_t NetIdCnt;
    float timer;
    struct UnityEngine_AddressableAssets_AssetReference_array* SpawnableObjects;
    struct InnerNet_InnerNetObject_array* NonAddressableSpawnableObjects;
    bool InOnlineScene;
    struct System_Collections_Generic_HashSet_uint__o* DestroyedObjects;
    struct System_Collections_Generic_List_InnerNetObject__o* allObjects;
    struct System_Collections_Generic_Dictionary_uint__InnerNetObject__o* allObjectsFast;
    struct Hazel_MessageWriter_array* Streams;
    std::int32_t msgNum;
    struct System_String_o* networkAddress;
    std::int32_t networkPort;
    bool useDtls;
    struct Hazel_Udp_UnityUdpClientConnection_o* connection;
    std::int32_t mode;
    std::int32_t GameMode;
    std::int32_t GameId;
    std::int32_t HostId;
    std::int32_t ClientId;
    struct System_Collections_Generic_List_ClientData__o* allClients;
    struct CircleBuffer_ClientData__o* recentClients;
    std::int32_t LastDisconnectReason;
    struct System_String_o* LastCustomDisconnect;
    std::uint8_t LastServerChatMode;
    struct System_Collections_Generic_List_Action__o* PreSpawnDispatcher;
    struct System_Collections_Generic_List_Action__o* Dispatcher;
    bool _IsGamePublic_k__BackingField;
    GameStates GameState;
    bool isConnecting;
    bool platformSpecificsChecked;
    struct System_Collections_Generic_List_Action__o* TempQueue;
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
            case game_version::v2022_3_29s:  return Class<InnerNetClient>::find("InnerNet", "InnerNetClient");
        }
        return nullptr;
    }

    ClientData* GetClientFromCharacter(InnerNetObject* character) {
        return get_cached_method<&InnerNetClient::GetClientFromCharacter>("GetClientFromCharacter")(this, character);
    }

    // No [marker], name shouldn't change
    void Update();
};
CHECK_TYPE(InnerNetClient, 0x84);

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
        case game_version::v2022_3_29s:  return "Update";
    }
    return nullptr;
}
