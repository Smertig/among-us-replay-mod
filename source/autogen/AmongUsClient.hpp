#pragma once

#include <autogen/InnerNet/InnerNetClient.hpp>

// KIIHPMJOOGI in 2020.10.8i
// JNFEHNLGIFF in 2020.10.22s
// HJNEPPHDLBA in 2020.11.4s
// MMMGPAPEEBJ in 2020.11.17s
// FMLLKEACGIO in 2020.12.9s
// AmongUsClient in 2021.3.5s
struct AmongUsClient : InnerNet::InnerNetClient {
    // std::int32_t AutoOpenStore; // until 2021.3.5s
    std::int32_t GameMode;
    struct System_String_o* OnlineScene;
    struct System_String_o* MainMenuScene;
    struct GameData_o* GameDataPrefab;
    struct PlayerControl_o* PlayerPrefab;
    struct System_Collections_Generic_List_AssetReference__o* ShipPrefabs; // type changed in 2021.3.5s
    struct System_Collections_Generic_List_GameObject__o* NonAddressableShipPrefabs; // since 2021.3.5s
    std::int32_t TutorialMapId;
    float SpawnRadius;
    std::int32_t discoverState;
    struct System_Collections_Generic_List_IDisconnectHandler__o* DisconnectHandlers;
    struct System_Collections_Generic_List_IGameListHandler__o* GameListHandlers;

    struct StaticFields {
        AmongUsClient* Instance;
    };

    static Class<AmongUsClient>* get_class() {
        switch (mod_info::get_game_version()) {
            case game_version::v2020_6_9s:   return Class<AmongUsClient>::find("AmongUsClient");
            case game_version::v2020_9_22s:  return Class<AmongUsClient>::find("AmongUsClient");
            case game_version::v2020_10_8i:  return Class<AmongUsClient>::find("KIIHPMJOOGI");
            case game_version::v2020_10_22s: return Class<AmongUsClient>::find("JNFEHNLGIFF");
            case game_version::v2020_11_4s:  return Class<AmongUsClient>::find("HJNEPPHDLBA");
            case game_version::v2020_11_17s: return Class<AmongUsClient>::find("MMMGPAPEEBJ");
            case game_version::v2020_12_9s:  return Class<AmongUsClient>::find("FMLLKEACGIO");
            case game_version::v2021_3_5s:   return Class<AmongUsClient>::find("AmongUsClient");
        }
        return nullptr;
    }

    static AmongUsClient* Instance() {
        return get_class()->statics()->Instance;
    }
};
CHECK_TYPE(AmongUsClient, 0xA0);
