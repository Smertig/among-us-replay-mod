#pragma once

#include <autogen/UnityEngine/Component.hpp>

namespace UnityEngine {

struct Behaviour : Component {
    bool isActiveAndEnabled() const {
        return get_cached_method<&Behaviour::isActiveAndEnabled>("get_isActiveAndEnabled")(this);
    }
};

} // namespace UnityEngine
