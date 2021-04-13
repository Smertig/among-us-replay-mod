#pragma once

#include "il2cpp_core.hpp"
#include "dynamic_proc.hpp"

#include <rcmp/low_level.hpp>
#include <fmt/format.h>
#include <spdlog/spdlog.h>

inline const auto il2cpp_class_get_method_from_name = dynamic_proc<const il2cpp::MethodInfo*(il2cpp::Il2CppClass*, const char*, int)>("GameAssembly.dll", "il2cpp_class_get_method_from_name");
inline const auto il2cpp_class_from_name = dynamic_proc<il2cpp::Il2CppClass*(const il2cpp::Il2CppImage*, const char*, const char*)>("GameAssembly.dll", "il2cpp_class_from_name");
inline const auto il2cpp_domain_get = dynamic_proc<il2cpp::Il2CppDomain*()>("GameAssembly.dll", "il2cpp_domain_get");
inline const auto il2cpp_domain_get_assemblies = dynamic_proc<const il2cpp::Il2CppAssembly**(const il2cpp::Il2CppDomain*, size_t*)>("GameAssembly.dll", "il2cpp_domain_get_assemblies");
inline const auto il2cpp_assembly_get_image = dynamic_proc<const il2cpp::Il2CppImage*(const il2cpp::Il2CppAssembly*)>("GameAssembly.dll", "il2cpp_assembly_get_image");
inline const auto il2cpp_method_get_param_count = dynamic_proc<uint32_t(const il2cpp::MethodInfo*)>("GameAssembly.dll", "il2cpp_method_get_param_count");
inline const auto il2cpp_method_get_name = dynamic_proc<const char*(const il2cpp::MethodInfo*)>("GameAssembly.dll", "il2cpp_method_get_name");
inline const auto il2cpp_class_get_type = dynamic_proc<const il2cpp::Il2CppType*(const il2cpp::Il2CppClass*)>("GameAssembly.dll", "il2cpp_class_get_type");
inline const auto il2cpp_type_get_name = dynamic_proc<const char*(const il2cpp::Il2CppType*)>("GameAssembly.dll", "il2cpp_type_get_name");

inline il2cpp::Il2CppClass* find_class(const char* namespace_, const char* class_) {
    spdlog::trace("looking for class {} in namespace {}", class_, namespace_[0] ? namespace_ : "(none)");

    auto dom = il2cpp_domain_get();

    std::size_t assembly_count = 0;
    const auto assemblies = il2cpp_domain_get_assemblies(dom, &assembly_count);

    for (auto it = assemblies; it != assemblies + assembly_count; ++it) {
        auto img = il2cpp_assembly_get_image(*it);
        if (!img) {
            spdlog::trace("null assembly..");
            continue;
        }

        auto cls = il2cpp_class_from_name(img, namespace_, class_);
        if (!cls) {
            continue;
        }

        spdlog::info("class found!");
        return cls;
    }

    spdlog::error("class not found..");
    return nullptr;
}

inline void dump_methods(il2cpp::Il2CppClass* class_) {
    if (class_->_2.method_count && !(class_->_1.methods)) {
        spdlog::error("Class is valid and claims to have methods but ->methods is null! class name: {}", class_->_1.name);
        return;
    }

    for (uint16_t i = 0; i < class_->_2.method_count; i++) {
        auto method = ((il2cpp::MethodInfo**)class_->_1.methods)[i];
        if (!method) {
            spdlog::error("#{} is null", i);
            continue;
        }

        spdlog::info("#{} -> {} ({} args)", i, il2cpp_method_get_name(method), il2cpp_method_get_param_count(method));
    }
}

namespace detail {
    template <class Signature>
    constexpr std::size_t arg_count_v = std::size_t(-1);

    template <class Ret, class... Args>
    constexpr std::size_t arg_count_v<Ret(*)(Args...)> = sizeof...(Args);
}

template <class Signature>
Signature find_method(il2cpp::Il2CppClass* class_, const char* method) {
    constexpr auto args_count = detail::arg_count_v<Signature>;
    static_assert(args_count != std::size_t(-1), "invalid signature");
    static_assert(args_count != std::size_t(0), "missing self type");

    spdlog::trace("looking for method {} with {} arg(s) in class {}", method, args_count - 1, class_->_1.name);
    auto method_ptr = il2cpp_class_get_method_from_name(class_, method, static_cast<int>(args_count) - 1);

    if (!method_ptr) {
        spdlog::error("method not found..");
        dump_methods(class_);
        return nullptr;
    }

    spdlog::info("method found: {:p} (address: {:p})!", fmt::ptr(method_ptr), rcmp::bit_cast<void*>(method_ptr->methodPointer));
    return rcmp::bit_cast<Signature>(method_ptr->methodPointer);
}

template <class Signature>
Signature find_static_method(il2cpp::Il2CppClass* class_, const char* method) {
    constexpr auto args_count = detail::arg_count_v<Signature>;
    static_assert(args_count != std::size_t(-1), "invalid signature");

    spdlog::trace("looking for static method {} with {} arg(s) in class {}", method, args_count, class_->_1.name);
    auto method_ptr = il2cpp_class_get_method_from_name(class_, method, static_cast<int>(args_count));

    if (!method_ptr) {
        spdlog::error("static method not found..");
        dump_methods(class_);
        return nullptr;
    }

    spdlog::info("static method found: {:p} (address: {:p})!", fmt::ptr(method_ptr), rcmp::bit_cast<void*>(method_ptr->methodPointer));
    return rcmp::bit_cast<Signature>(method_ptr->methodPointer);
}

template <class Signature>
Signature find_method(const char* namespace_, const char* class_, const char* method) {
    auto cls = find_class(namespace_, class_);
    if (!cls) {
        return nullptr;
    }

    return find_method<Signature>(cls, method);
}

template <class Signature>
Signature find_static_method(const char* namespace_, const char* class_, const char* method) {
    auto cls = find_class(namespace_, class_);
    if (!cls) {
        return nullptr;
    }

    return find_static_method<Signature>(cls, method);
}
