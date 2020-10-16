#pragma once

#include <utils/il2cpp.hpp>
#include <utils/mod_info.hpp>
#include <cstddef>
#include <cstdint>
#include <type_traits>

#include <rcmp/low_level.hpp>

#define CHECK_TYPE(Type, Size) static_assert(sizeof(Type) == Size + sizeof(il2cpp::Il2CppObject)); static_assert(std::is_base_of_v<il2cpp::Il2CppObject, Type>)

template <class T>
struct Class : il2cpp::Il2CppClass {
    template <class U = T>
    auto statics() -> typename U::StaticFields* {
        return reinterpret_cast<typename U::StaticFields*>(this->static_fields);
    }

    template <class Signature>
    Signature get_method(const char* name) {
        return ::find_static_method<Signature>(this, name);
    }

    static Class* get() {
        return T::get_class();
    }

    static Class* find(const char* namespace_, const char* class_) {
        static const auto result = reinterpret_cast<Class<T>*>(::find_class(namespace_, class_));
        return result;
    }

    static Class* find(const char* class_) {
        return find("", class_);
    }
};

struct Object : il2cpp::Il2CppObject {
    template <class Signature>
    Signature get_method(const char* name) const {
        return ::find_method<Signature>(this->klass, name);
    }

    template <auto Method>
    auto get_cached_method(const char* name) const {
        using Signature = rcmp::flatten_pmf_t<decltype(Method), rcmp::cconv::cdecl_>;
        static const auto method = get_method<Signature>(name);
        return method;
    }
};

CHECK_TYPE(Object, 0);

template <class T>
struct Array {
    il2cpp::Il2CppObject obj;
    il2cpp::Il2CppArrayBounds *bounds;
    il2cpp::il2cpp_array_size_t max_length;
    T* m_Items[65535];
};

template <auto>
const char* get_method_name();
