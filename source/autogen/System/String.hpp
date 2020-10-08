#pragma once

#include <autogen/Object.hpp>
#include <utils/encoding.hpp>

namespace System {

struct String : ::Object {
    std::int32_t m_stringLength;
    char16_t m_firstChar;

    std::u16string_view to_view() const {
        return { &m_firstChar, static_cast<std::size_t>(m_stringLength) };
    }

    std::string to_utf8() const {
        return ::to_utf8(to_view());
    }
};
CHECK_TYPE(String, 0x8);

} // namespace System