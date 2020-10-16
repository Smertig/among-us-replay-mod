#pragma once

#include <autogen/Object.hpp>

namespace UnityEngine {

struct Object : ::Object {
    std::intptr_t m_CachedPtr;

    bool is_null() const {
        return m_CachedPtr == 0;
    }
};
CHECK_TYPE(Object, 0x4);

inline bool is_null(const Object* ptr) {
    return ptr == nullptr || ptr->is_null();
}

} // namespace UnityEngine
