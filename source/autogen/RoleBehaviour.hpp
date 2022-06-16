#pragma once

#include <autogen/UnityEngine/MonoBehaviour.hpp>

struct PlayerControl;

// RoleBehaviour since 2022.3.29s
struct RoleBehaviour : UnityEngine::MonoBehaviour {
    std::uint16_t Role;
    std::int32_t StringName;
    std::int32_t BlurbName;
    std::int32_t BlurbNameMed;
    std::int32_t BlurbNameLong;
    UnityEngine::Color NameColor;
    bool TasksCountTowardProgress;
    bool CanUseKillButton;
    bool CanBeKilled;
    bool CanVent;
    bool AffectedByLightAffectors;
    std::int32_t MaxCount;
    std::int32_t TeamType;
    struct AbilityButtonSettings_o* Ability;
    struct UnityEngine_AudioClip_o* UseSound;
    struct UnityEngine_AudioClip_o* IntroSound;
    PlayerControl* Player;

    bool get_IsImpostor() const {
        return get_cached_method<&RoleBehaviour::get_IsImpostor>("get_IsImpostor")(this);
    }
};
CHECK_TYPE(RoleBehaviour, 0x48);
