#pragma once

#include <string>
#include <chrono>

namespace utils {

std::string get_date_string(std::chrono::system_clock::time_point t);

void msgbox_error(const std::string& text);

bool msgbox_warning_yesno(const std::string& text);

} // namespace utils
