#pragma once

#include <chrono>

#include <fmt/format.h>
#include <spdlog/spdlog.h>

class periodic_printer {
    using clock_t = std::chrono::steady_clock;

    std::string m_prefix;
    clock_t::duration m_period;
    clock_t::time_point m_next_call;

public:
    explicit periodic_printer(std::string prefix, clock_t::duration period) : m_prefix(std::move(prefix)), m_period(period), m_next_call() {
        // nothing
    }

    auto get_printer() {
        const auto now = clock_t::now();

        bool should_print = false;
        if (now > m_next_call) {
            should_print = true;
            m_next_call = now + m_period;
        }

        return [should_print, this](auto&& ...args) {
            if (!should_print) {
                return;
            }

            spdlog::info("{}: {}", m_prefix, fmt::format(std::forward<decltype(args)>(args)...));
        };
    }
};
