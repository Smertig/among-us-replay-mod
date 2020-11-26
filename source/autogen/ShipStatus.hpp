#pragma once

#include <autogen/InnerNet/InnerNetObject.hpp>
#include <autogen/UnityEngine/Vector2.hpp>
#include <autogen/UnityEngine/Color.hpp>

// FMDGHKGPBPP in 2020.10.8i
// DAFPFFMKPJJ in 2020.10.22s
// OLEKJGCEKAM in 2020.11.4s
// EIEMHBCHLNI in 2020.11.17s
struct ShipStatus : InnerNet::InnerNetObject {
    enum class MapType : std::int32_t {
        Ship = 0,
        Hq = 1,
        Pb = 2,
    };

    UnityEngine::Color CameraColor;
    float MaxLightRadius; // [marker]
    float MinLightRadius;
    float MapScale;
    struct MapBehaviour_o* MapPrefab;
    struct ExileController_o* ExileCutscenePrefab;
    UnityEngine::Vector2 InitialSpawnCenter;
    UnityEngine::Vector2 MeetingSpawnCenter;
    UnityEngine::Vector2 MeetingSpawnCenter2;
    float SpawnRadius;
    struct NormalPlayerTask_array* CommonTasks;
    struct NormalPlayerTask_array* LongTasks;
    struct NormalPlayerTask_array* NormalTasks;
    struct PlayerTask_array* SpecialTasks;
    struct UnityEngine_Transform_array* DummyLocations;
    struct SurvCamera_array* AllCameras;
    struct PlainDoor_array* AllDoors;
    struct Console_array* AllConsoles;
    struct System_Collections_Generic_Dictionary_HBKFJKIHEFM__GCEKFCICMHL__o* Systems;
    struct AKPFLLKKOBN_array* _HMALBFKGHFE_k__BackingField;
    struct PlainShipRoom_array* _PDBPIILBHAE_k__BackingField;
    struct System_Collections_Generic_Dictionary_HBKFJKIHEFM__PlainShipRoom__o* _FNFHCOHJDBK_k__BackingField;
    struct Vent_array* _LFOLHNDFOLH_k__BackingField;
    struct UnityEngine_AnimationClip_array* WeaponFires;
    struct PowerTools_SpriteAnim_o* WeaponsImage;
    struct UnityEngine_AudioClip_array* VentMoveSounds;
    struct UnityEngine_AudioClip_o* VentEnterSound;
    struct UnityEngine_AnimationClip_o* HatchActive;
    struct PowerTools_SpriteAnim_o* Hatch;
    struct UnityEngine_ParticleSystem_o* HatchParticles;
    struct UnityEngine_AnimationClip_o* ShieldsActive;
    struct PowerTools_SpriteAnim_array* ShieldsImages;
    struct UnityEngine_SpriteRenderer_o* ShieldBorder;
    struct UnityEngine_Sprite_o* ShieldBorderOn;
    struct MedScannerBehaviour_o* MedScanner;
    std::int32_t WeaponFireIdx;
    float Timer;
    float EmergencyCooldown;
    MapType Type;
    // std::int32_t HBFNNGCEGNI; // since 2020.10.8i

    struct StaticFields {
        ShipStatus* Instance;
    };

    static Class<ShipStatus>* get_class() {
        switch (mod_info::get_game_version()) {
            case game_version::v2020_6_9s:   return Class<ShipStatus>::find("ShipStatus");
            case game_version::v2020_9_22s:  return Class<ShipStatus>::find("ShipStatus");
            case game_version::v2020_10_8i:  return Class<ShipStatus>::find("FMDGHKGPBPP");
            case game_version::v2020_10_22s: return Class<ShipStatus>::find("DAFPFFMKPJJ");
            case game_version::v2020_11_4s:  return Class<ShipStatus>::find("OLEKJGCEKAM");
            case game_version::v2020_11_17s: return Class<ShipStatus>::find("EIEMHBCHLNI");
        }
        return nullptr;
    }

    static ShipStatus* instance() {
        return get_class()->statics()->Instance;
    }

    // No [marker], name shouldn't change
    void Begin();
};
CHECK_TYPE(ShipStatus, 0xD0);

template <>
const char* get_method_name<&ShipStatus::Begin>() {
    switch (mod_info::get_game_version()) {
        case game_version::v2020_6_9s:   return "Begin";
        case game_version::v2020_9_22s:  return "Begin";
        case game_version::v2020_10_8i:  return "Begin";
        case game_version::v2020_10_22s: return "Begin";
        case game_version::v2020_11_4s:  return "Begin";
        case game_version::v2020_11_17s: return "Begin";
    }
    return nullptr;
}
