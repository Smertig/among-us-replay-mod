#pragma once

#include <autogen/InnerNet/InnerNetObject.hpp>
#include <autogen/System/Collections/Generic/List.hpp>
#include <autogen/System/String.hpp>

struct PlayerControl;

struct GameData : InnerNet::InnerNetObject {
    // GameData.CBOMPDNBEIF since 2020.9.22
    struct TaskInfo : ::Object {
        std::uint32_t Id;
        std::uint8_t TypeId;
        bool Complete;
    };
    CHECK_TYPE(TaskInfo, 0x8);

    // GameData.IHEKEPMDGIJ since 2020.9.22
    struct PlayerInfo : ::Object {
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

    System::Collections::Generic::List<PlayerInfo>* AllPlayers;
    std::int32_t TotalTasks;
    std::int32_t CompletedTasks;

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
CHECK_TYPE(GameData, 0x28);
