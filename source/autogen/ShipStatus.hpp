#pragma once

#include <autogen/InnerNet/InnerNetObject.hpp>
#include <autogen/UnityEngine/Vector2.hpp>
#include <autogen/UnityEngine/Color.hpp>

struct ShipStatus : InnerNet::InnerNetObject {
    UnityEngine::Color CameraColor;
    float MaxLightRadius;
    float MinLightRadius;
    float MapScale;
    struct MapBehaviour_o* MapPrefab;
    struct ExileController_o* ExileCutscenePrefab;
    struct MeetingCalledAnimation_o* EmergencyOverlay;
    struct MeetingCalledAnimation_o* ReportOverlay;
    struct UnityEngine_Sprite_o* MeetingBackground;
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
    struct System_Collections_Generic_Dictionary_SystemTypes__ISystemType__o* Systems;
    struct StringNames_array* SystemNames;
    struct IStepWatcher_array* _AllStepWatchers_k__BackingField;
    struct PlainShipRoom_array* _AllRooms_k__BackingField;
    struct System_Collections_Generic_Dictionary_SystemTypes__PlainShipRoom__o* _FastRooms_k__BackingField;
    struct Vent_array* _AllVents_k__BackingField;
    struct UnityEngine_AudioClip_o* SabotageSound;
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
    std::int32_t Type;
    bool _BeginCalled_k__BackingField;
    float _HideCountdown_k__BackingField;
    struct CosmeticsCache_o* _CosmeticsCache_k__BackingField;
    std::int32_t numScans;

    struct StaticFields {
        ShipStatus* Instance;
    };

    static Class<ShipStatus>* get_class() {
        return Class<ShipStatus>::find("ShipStatus");
    }

    static ShipStatus* instance() {
        return get_class()->statics()->Instance;
    }

    void Begin();
};
CHECK_TYPE(ShipStatus, 0xF4);

template <>
const char* get_method_name<&ShipStatus::Begin>() {
    return "Begin";
}
