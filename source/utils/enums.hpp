#pragma once

#include <magic_enum.hpp>
#include <fmt/format.h>

template <class E>
struct fmt::formatter<E, char, std::enable_if_t<magic_enum::is_scoped_enum_v<E>>> : fmt::formatter<std::string_view> {
    auto format(E value, format_context& ctx) {
        return formatter<std::string_view>::format(magic_enum::enum_name(value), ctx);
    }
};
