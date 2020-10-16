#pragma once

#include <autogen/InnerNet/InnerNetObject.hpp>
#include <autogen/System/Collections/Generic/List.hpp>
#include <autogen/System/String.hpp>

struct PlayerControl;

// KIOIFEIADMB in 2020.10.8i
struct GameData : InnerNet::InnerNetObject {
    // GameData.CBOMPDNBEIF in 2020.9.22
    // KIOIFEIADMB.FAECJOFPICI in 2020.10.8i
    struct TaskInfo : ::Object {
        // [marker] is PlayerInfo.Tasks
        std::uint32_t Id;
        std::uint8_t TypeId;
        bool Complete;
    };
    CHECK_TYPE(TaskInfo, 0x8);

    // GameData.IHEKEPMDGIJ in 2020.9.22
    // KIOIFEIADMB.IOHELPMOCLM in 2020.10.8i
    struct PlayerInfo : ::Object {
        // no [marker], search for 'killer'
        std::uint8_t PlayerId;
        System::String* PlayerName;
        std::uint8_t ColorId;
        std::uint32_t HatId;
        std::uint32_t PetId;
        std::uint32_t SkinId;
        bool Disconnected;
        System::Collections::Generic::List<TaskInfo>* Tasks;
        bool IsImpostor;
        bool IsDead;
        PlayerControl *_object;
    };
    CHECK_TYPE(PlayerInfo, 0x28);

    System::Collections::Generic::List<PlayerInfo>* AllPlayers; // [marker]
    std::int32_t TotalTasks;
    std::int32_t CompletedTasks;

    struct StaticFields {
        GameData* instance;
    };

    static Class<GameData>* get_class() {
        switch (mod_info::get_game_version()) {
            case game_version::v2020_6_9s:  return Class<GameData>::find("GameData");
            case game_version::v2020_9_22s: return Class<GameData>::find("GameData");
            case game_version::v2020_10_8i: return Class<GameData>::find("KIOIFEIADMB");
        }
        return nullptr;
    }

    static GameData* instance() {
        return get_class()->statics()->instance;
    }
};
CHECK_TYPE(GameData, 0x28);
