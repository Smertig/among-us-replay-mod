#pragma once

#include <autogen/InnerNet/InnerNetObject.hpp>
#include <autogen/System/Collections/Generic/List.hpp>
#include <autogen/System/Collections/Generic/Dictionary.hpp>
#include <autogen/System/String.hpp>
#include <autogen/PlayerOutfitType.hpp>

struct PlayerControl;
struct RoleBehaviour;

// il2cpp: struct GameData_Fields
struct GameData : InnerNet::InnerNetObject {
    // il2cpp: struct GameData_TaskInfo_Fields
    struct TaskInfo : ::Object {
        std::uint32_t Id;
        std::uint8_t TypeId;
        bool Complete;
    };
    CHECK_TYPE(TaskInfo, 0x8);

    // il2cpp: struct GameData_PlayerOutfit_Fields
    struct PlayerOutfit : ::Object {
        bool dontCensorName;
        std::int32_t ColorId;
        System::String* HatId;
        System::String* PetId;
        System::String* SkinId;
        System::String* VisorId;
        System::String* NamePlateId;
        System::String* _playerName;
        System::String* preCensorName;
        System::String* postCensorName;
    };
    CHECK_TYPE(PlayerOutfit, 0x28);

    // il2cpp: struct GameData_PlayerInfo_Fields
    struct PlayerInfo : ::Object {
        std::uint8_t PlayerId;
        System::String* FriendCode;
        System::String* Puid;
        System::Collections::Generic::Dictionary<PlayerOutfitType, PlayerOutfit>* Outfits;
        std::uint32_t PlayerLevel;
        bool Disconnected;
        RoleBehaviour* Role;
        System::Collections::Generic::List<TaskInfo*>* Tasks;
        bool IsDead;
        PlayerControl* _object;

        System::String* get_PlayerName() const {
            return get_cached_method<&PlayerInfo::get_PlayerName>("get_PlayerName")(this);
        }
    };
    CHECK_TYPE(PlayerInfo, 0x28);

    System::Collections::Generic::List<PlayerInfo*>* AllPlayers;
    std::int32_t TotalTasks;
    std::int32_t CompletedTasks;
    struct RoleBehaviour_o* DefaultRole;

    // il2cpp: struct GameData_StaticFields
    struct StaticFields {
        GameData* instance;
    };

    static Class<GameData>* get_class() {
        return Class<GameData>::find("GameData");
    }

    static GameData* instance() {
        return get_class()->statics()->instance;
    }
};
CHECK_TYPE(GameData, 0x2C);
