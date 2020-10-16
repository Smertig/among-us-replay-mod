#pragma once

#include "il2cpp.hpp"

#include <rcmp/codegen.hpp>
#include <autogen/Object.hpp>

template <class Signature, class F>
void hook_method(const char* namespace_, const char* class_, const char* method, F&& callback) {
    fmt::print("try hook {}::{}::{}\n", namespace_, class_, method);

    auto method_address = rcmp::bit_cast<std::uintptr_t>(find_method<Signature>(namespace_, class_, method));
    if (!method_address) {
        fmt::print("unable to hook - method not found\n");
        return;
    }

    rcmp::hook_function<Signature>(method_address, std::forward<F>(callback));
}

template <class Signature, class F>
void hook_method(const char* class_, const char* method, F&& callback) {
    hook_method<Signature>("", class_, method, std::forward<F>(callback));
}

namespace detail {

template <class Signature>
struct get_class_impl;

template <class Class, class Ret, class... Args>
struct get_class_impl<Ret(Class::*)(Args...)> {
    using type = Class;
};

template <class Class, class Ret, class... Args>
struct get_class_impl<Ret(Class::*)(Args...) const> {
    using type = Class;
};

} // namespace detail

template <auto Method, class F>
void hook_method(F&& callback) {
    using method_t = decltype(Method);
    using class_t = typename detail::get_class_impl<method_t>::type;

    ::il2cpp::Il2CppClass* class_ = class_t::get_class();
    if (!class_) {
        fmt::print("unable to hook - class not found\n");
        return;
    }

    ::hook_method<rcmp::flatten_pmf_t<method_t, rcmp::cconv::cdecl_>>(class_->_1.namespaze, class_->_1.name, ::get_method_name<Method>(), std::forward<F>(callback));
}
