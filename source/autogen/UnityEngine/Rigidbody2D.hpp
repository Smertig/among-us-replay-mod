#pragma once

#include <autogen/UnityEngine/Component.hpp>
#include <autogen/UnityEngine/Vector2.hpp>

namespace UnityEngine {

struct Rigidbody2D : Component {
    Vector2 get_position() const {
        return get_cached_method<&Rigidbody2D::get_position>("get_position")(this);
    }

    Vector2 get_velocity() const {
        return get_cached_method<&Rigidbody2D::get_velocity>("get_velocity")(this);
    }
};
CHECK_TYPE(Rigidbody2D, 0x4);

} // namespace UnityEngine
