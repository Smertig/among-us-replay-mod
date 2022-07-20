#include "utils.hpp"
#include "mod_info.hpp"

#include <fmt/format.h>

#include <stdexcept>
#include <ctime>

#include <Windows.h>

std::string utils::get_date_string(std::chrono::system_clock::time_point t) {
    const auto time = std::chrono::system_clock::to_time_t(t);

    std::tm tm{};
    if (::localtime_s(&tm, &time)) {
        throw std::runtime_error("unable to call localtime_s");
    }

    char buffer[0x100];
    if (!std::strftime(buffer, std::size(buffer), "%Y_%m_%d-%H_%M_%S", &tm)) {
        throw std::runtime_error("unable to call strftime");
    }

    return buffer;
}

static std::string get_msgbox_caption() {
    return fmt::format("{} v{}", mod_info::mod_name, mod_info::mod_version);
}

void utils::msgbox_error(const std::string& text) {
    MessageBoxA(nullptr, text.c_str(), get_msgbox_caption().c_str(), MB_ICONERROR);
}

bool utils::msgbox_warning_yesno(const std::string& text) {
    const auto result = MessageBoxA(nullptr, text.c_str(), get_msgbox_caption().c_str(), MB_ICONEXCLAMATION | MB_YESNO);
    return result == IDYES;
}
