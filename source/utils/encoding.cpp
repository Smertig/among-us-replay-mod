#include "encoding.hpp"

#include <Windows.h>

std::string to_utf8(std::u16string_view input) {
    static_assert(sizeof(wchar_t) == sizeof(char16_t));

    if (input.empty()) {
        return {};
    }

    const auto input_data = reinterpret_cast<const wchar_t*>(input.data());
    const auto input_size = static_cast<int>(input.size());

    const auto output_size = ::WideCharToMultiByte(CP_UTF8, 0, input_data, input_size, nullptr, 0, nullptr, nullptr);

    std::string result(output_size, '\0');
    ::WideCharToMultiByte(CP_UTF8, 0, input_data, input_size, &result[0], output_size, nullptr, nullptr);

    return result;
}
