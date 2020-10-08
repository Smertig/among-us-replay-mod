#pragma once

#include <Windows.h>

#include <string>

template <class Signature>
struct dynamic_proc;

template <class Ret, class... Args>
struct dynamic_proc<Ret(Args...)> {
    dynamic_proc(const char* dll_name, const char* proc_name) noexcept {
        m_address = GetProcAddress(GetModuleHandleA(dll_name), proc_name);
    }

    Ret operator()(Args... args) const {
        return reinterpret_cast<Ret(*)(Args...)>(m_address)(std::move(args)...);
    }

private:
    FARPROC m_address;
};
