#pragma once

#include <autogen/InnerNet/InnerNetObject.hpp>
#include <autogen/System/Collections/Generic/List.hpp>

struct PlayerTask;
struct CustomNetworkTransform;

struct PlayerControl : InnerNet::InnerNetObject {
    std::int32_t LastStartCounter;
    std::uint8_t PlayerId;
    float MaxReportDistance;
    bool moveable;
    bool inVent;
    struct GameData_PlayerInfo_o *_cachedData;
    struct UnityEngine_AudioSource_o *FootSteps;
    struct UnityEngine_AudioClip_o *KillSfx;
    struct KillAnimation_array *KillAnimations;
    float killTimer;
    std::int32_t RemainingEmergencies;
    struct TextRenderer_o *nameText;
    struct LightSource_o *LightPrefab;
    struct LightSource_o *myLight;
    struct UnityEngine_Collider2D_o *Collider;
    struct PlayerPhysics_o *MyPhysics;
    CustomNetworkTransform *NetTransform;
    struct PetBehaviour_o *CurrentPet;
    struct HatParent_o *HatRenderer;
    struct UnityEngine_SpriteRenderer_o *myRend;
    struct UnityEngine_Collider2D_array *hitBuffer;
    System::Collections::Generic::List<PlayerTask>* myTasks;
    struct PowerTools_SpriteAnim_array *ScannerAnims;
    struct UnityEngine_SpriteRenderer_array *ScannersImages;
    struct IUsable_o *closest;
    bool isNew;
    struct System_Collections_Generic_Dictionary_Collider2D__IUsable__o *cache;
    struct System_Collections_Generic_List_IUsable__o *itemsInRange;
    struct System_Collections_Generic_List_IUsable__o *newItemsInRange;
    std::uint8_t scannerCount;
    bool infectedSet;
};
CHECK_TYPE(PlayerControl, 0x90);
