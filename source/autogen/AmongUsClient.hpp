#pragma once

#include <autogen/InnerNet/InnerNetClient.hpp>

// il2cpp: struct AmongUsClient_Fields
struct AmongUsClient : InnerNet::InnerNetClient {
    struct System_String_o* OnlineScene;
    struct System_String_o* MainMenuScene;
    struct GameData_o* GameDataPrefab;
    struct PlayerControl_o* PlayerPrefab;
    struct System_Collections_Generic_List_AssetReference__o* ShipPrefabs;
    std::int32_t TutorialMapId;
    float SpawnRadius;
    std::int32_t discoverState;
    struct System_Collections_Generic_List_IDisconnectHandler__o* DisconnectHandlers;
    struct System_Collections_Generic_List_IGameListHandler__o* GameListHandlers;
    std::int32_t CrossplayPrivilegeError;

    // il2cpp: struct AmongUsClient_StaticFields
    struct StaticFields {
        AmongUsClient* Instance;
    };

    static Class<AmongUsClient>* get_class() {
        return Class<AmongUsClient>::find("AmongUsClient");
    }

    static AmongUsClient* Instance() {
        return get_class()->statics()->Instance;
    }
};
CHECK_TYPE(AmongUsClient, 0xB0);
