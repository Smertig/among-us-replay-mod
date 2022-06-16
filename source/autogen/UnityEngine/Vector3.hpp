#pragma once

namespace UnityEngine {

struct Vector3 {
    float x;
    float y;
    float z;

    friend auto operator<=>(const Vector3&, const Vector3&) = default;
};

} // namespace UnityEngine
