#pragma once

#include <autogen/InnerNet/InnerNetObject.hpp>
#include <autogen/System/Collections/Generic/List.hpp>
#include <autogen/System/Collections/Generic/Dictionary.hpp>
#include <autogen/System/String.hpp>
#include <autogen/PlayerOutfitType.hpp>

struct PlayerControl;
struct RoleBehaviour;

// KIOIFEIADMB in 2020.10.8i
// BAGGGBBOHOH in 2020.10.22s
// BOMCDPPPECM in 2020.11.4s
// FLIHHNFFPAO in 2020.11.17s
// EGLJNOMOGNP in 2020.12.9s
// GameData since 2021.3.5s
struct GameData : InnerNet::InnerNetObject {
    // GameData.CBOMPDNBEIF in 2020.9.22
    // KIOIFEIADMB.FAECJOFPICI in 2020.10.8i
    // BAGGGBBOHOH.ALLADIFCEHO in 2020.10.22s
    // BOMCDPPPECM.IDFPHCCPCJC in 2020.11.4s
    // FLIHHNFFPAO.CJOIAHBNANN in 2020.11.17s
    // EGLJNOMOGNP.CAAACHLJJNE in 2020.12.9s
    // GameData.HKFJOIBBOBD in 2021.3.5s
    // GameData.NGBCKJFEBBJ in 2021.4.12s
    // GameData.TaskInfo since 2022.3.29s
    struct TaskInfo : ::Object {
        // [marker] is PlayerInfo.Tasks
        std::uint32_t Id;
        std::uint8_t TypeId;
        bool Complete;
    };
    CHECK_TYPE(TaskInfo, 0x8);

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

    // GameData.IHEKEPMDGIJ in 2020.9.22
    // KIOIFEIADMB.IOHELPMOCLM in 2020.10.8i
    // BAGGGBBOHOH.FGMBFCIIILC in 2020.10.22s
    // BOMCDPPPECM.FDGKOOFKODI in 2020.11.4s
    // FLIHHNFFPAO.LBGGNMFGAOO in 2020.11.17s
    // EGLJNOMOGNP.DCJMABDDJCF in 2020.12.9s
    // GameData.GOOIGLGKMCE in 2021.3.5s
    // GameData.LGBOMGHJELL in 2021.4.12s
    // GameData.PlayerInfo since 2022.3.29s
    struct PlayerInfo : ::Object {
        // [marker] is GameData.AllPlayers
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

    System::Collections::Generic::List<PlayerInfo*>* AllPlayers; // [marker]
    std::int32_t TotalTasks;
    std::int32_t CompletedTasks;
    struct RoleBehaviour_o* DefaultRole;

    struct StaticFields {
        GameData* instance;
    };

    static Class<GameData>* get_class() {
        switch (mod_info::get_game_version()) {
            case game_version::v2020_6_9s:   return Class<GameData>::find("GameData");
            case game_version::v2020_9_22s:  return Class<GameData>::find("GameData");
            case game_version::v2020_10_8i:  return Class<GameData>::find("KIOIFEIADMB");
            case game_version::v2020_10_22s: return Class<GameData>::find("BAGGGBBOHOH");
            case game_version::v2020_11_4s:  return Class<GameData>::find("BOMCDPPPECM");
            case game_version::v2020_11_17s: return Class<GameData>::find("FLIHHNFFPAO");
            case game_version::v2020_12_9s:  return Class<GameData>::find("EGLJNOMOGNP");
            case game_version::v2021_3_5s:   return Class<GameData>::find("GameData");
            case game_version::v2021_4_12s:  return Class<GameData>::find("GameData");
            case game_version::v2022_3_29s:  return Class<GameData>::find("GameData");
        }
        return nullptr;
    }

    static GameData* instance() {
        return get_class()->statics()->instance;
    }
};
CHECK_TYPE(GameData, 0x2C);
