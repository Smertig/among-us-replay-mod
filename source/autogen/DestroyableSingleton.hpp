#pragma once

#include <autogen/UnityEngine/MonoBehaviour.hpp>

template <class T>
struct DestroyableSingleton : UnityEngine::MonoBehaviour {
    bool DontDestroy;

    struct StaticFields {
        T* _instance;
    };

    static Class<DestroyableSingleton<T>>* get_class() {
        return reinterpret_cast<Class<DestroyableSingleton<T>>*>(T::get_class()->_1.parent);
    }

    static T* Instance() {
        return get_class()->statics()->_instance;
    }
};
CHECK_TYPE(DestroyableSingleton<int>, 0x8);
