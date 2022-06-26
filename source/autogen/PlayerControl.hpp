#pragma once

#include <autogen/InnerNet/InnerNetObject.hpp>
#include <autogen/UnityEngine/Vector3.hpp>
#include <autogen/System/Collections/Generic/List.hpp>

struct PlayerTask;
struct CustomNetworkTransform;

// il2cpp: struct PlayerControl_Fields
struct PlayerControl : InnerNet::InnerNetObject {
    std::int32_t LastStartCounter;
    std::uint8_t PlayerId;
    System::String* FriendCode;
    System::String* Puid;
    float MaxReportDistance;
    bool moveable;
    struct System_Collections_Generic_List_PlayerBodySprite__o* BodySprites;
    struct PlayerBodySprite_o* CurrentBodySprite;
    struct PlayerBodySprite_o* NormalBodySprite;
    std::int32_t _CurrentOutfitType_k__BackingField;
    bool inVent;
    bool protectedByGuardianThisRound;
    bool shapeshifting;
    struct GameData_PlayerInfo_o* _cachedData;
    bool protectedByGuardian;
    float flashlightAngle;
    struct UnityEngine_AudioSource_o* FootSteps;
    struct UnityEngine_AudioClip_o* KillSfx;
    struct KillAnimation_array* KillAnimations;
    float killTimer;
    std::int32_t RemainingEmergencies;
    struct TMPro_TextMeshPro_o* nameText;
    struct LightSource_o* LightPrefab;
    struct LightSource_o* myLight;
    struct UnityEngine_Collider2D_o* Collider;
    struct PlayerPhysics_o* MyPhysics;
    CustomNetworkTransform* NetTransform;
    struct PetBehaviour_o* CurrentPet;
    struct HatParent_o* HatRenderer;
    struct VisorLayer_o* VisorSlot;
    struct PowerTools_SpriteAnim_o* myAnim;
    struct PowerTools_SpriteAnim_o* horseAnim;
    struct UnityEngine_Collider2D_array* hitBuffer;
    System::Collections::Generic::List<PlayerTask>* myTasks;
    UnityEngine::Vector3 defaultPlayerScale;
    struct PowerTools_SpriteAnim_array* ScannerAnims;
    struct UnityEngine_SpriteRenderer_array* ScannersImages;
    struct System_Collections_Generic_List_RoleEffectAnimation__o* currentRoleAnimations;
    struct IUsable_o* closest;
    bool isNew;
    bool isDummy;
    bool notRealPlayer;
    struct System_Collections_Generic_Dictionary_Collider2D__IUsable____o* cache;
    struct System_Collections_Generic_List_IUsable__o* itemsInRange;
    struct System_Collections_Generic_List_IUsable__o* newItemsInRange;
    std::uint8_t scannerCount;
    bool roleAssigned;

    static Class<PlayerControl>* get_class() {
        return Class<PlayerControl>::find("PlayerControl");
    }

    void SetTasks(void*);
};
CHECK_TYPE(PlayerControl, 0xCC);

template <>
const char* get_method_name<&PlayerControl::SetTasks>() {
    return "SetTasks";
}
