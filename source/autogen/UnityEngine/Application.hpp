#pragma once

#include <autogen/Object.hpp>

#include <string>

namespace UnityEngine {

struct Application : ::Object {
    static Class<Application>* get_class() {
        return Class<Application>::find("UnityEngine", "Application");
    }

    static std::string get_version() {
        static const auto m = get_class()->get_method<System::String*(*)()>("get_version");
        return m()->to_utf8();
    }
};

} // namespace UnityEngine
