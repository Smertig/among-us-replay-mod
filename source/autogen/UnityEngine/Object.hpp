#pragma once

#include <autogen/Object.hpp>

namespace UnityEngine {

struct Object : ::Object {
    std::intptr_t m_CachedPtr;
};

} // namespace UnityEngine
