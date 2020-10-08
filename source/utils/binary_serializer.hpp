#pragma once

#include <ostream>
#include <ctime>

#include <autogen/System/String.hpp>
#include <autogen/UnityEngine/Vector2.hpp>

class binary_serializer {
    std::ostream& m_os;

public:
    explicit binary_serializer(std::ostream& os) : m_os(os) {
        // nothing
    }

    void write(std::time_t tp) {
        static_assert(sizeof(tp) == 8);
        write(static_cast<std::uint64_t>(tp));
    }

    void write(const System::String* value) {
        write(value->to_utf8());
    }

    void write(std::string_view value) {
        write(static_cast<std::uint32_t>(value.size()));
        write(value.data(), value.size());
    }

    template <class T>
    void write(const T& value, std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>>* = nullptr) {
        write(&value, sizeof(value));
    }

    void write(const UnityEngine::Vector2& vec) {
        write(vec.x);
        write(vec.y);
    }

    template <class E>
    void write(const E& value, std::enable_if_t<std::is_enum_v<E>>* = nullptr) {
        write(static_cast<std::underlying_type_t<E>>(value));
    }

    template <class T>
    auto write(const T& value) -> decltype(value.write_to(*this)) {
        value.write_to(*this);
    }

    void write(const void* data, std::size_t size) {
        m_os.write(reinterpret_cast<const char*>(data), size);
    }
};
