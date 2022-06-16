#pragma once

#include <autogen/UnityEngine/MonoBehaviour.hpp>

namespace InnerNet {

struct ClientData;
struct InnerNetObject;

struct InnerNetClient : UnityEngine::MonoBehaviour {
    enum class GameStates : std::int32_t {
        NotJoined = 0,
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
        return Class<InnerNetClient>::find("InnerNet", "InnerNetClient");
    }

    ClientData* GetClientFromCharacter(InnerNetObject* character) {
        return get_cached_method<&InnerNetClient::GetClientFromCharacter>("GetClientFromCharacter")(this, character);
    }

    void Update();
};
CHECK_TYPE(InnerNetClient, 0x84);

} // namespace InnerNet

template <>
inline const char* get_method_name<&InnerNet::InnerNetClient::Update>() {
    return "Update";
}
