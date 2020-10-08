#pragma once

#include "il2cpp.hpp"

#include <rcmp/codegen.hpp>

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
