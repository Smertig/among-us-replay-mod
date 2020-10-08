#pragma once

#include <autogen/InnerNet/InnerNetObject.hpp>
#include <autogen/UnityEngine/Vector2.hpp>
#include <autogen/UnityEngine/Color.hpp>

struct ShipStatus : InnerNet::InnerNetObject {
    enum class MapType : std::int32_t {
        Ship = 0,
        Hq = 1,
        Pb = 2,
    };

    UnityEngine::Color CameraColor;
    float MaxLightRadius;
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

    static Class<ShipStatus>* get_class() {
        return Class<ShipStatus>::find("ShipStatus");
    }
};
CHECK_TYPE(ShipStatus, 0xD0);
