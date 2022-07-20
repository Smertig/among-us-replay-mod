#include "logger.hpp"
#include "utils.hpp"
#include "mod_info.hpp"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <autogen/UnityEngine/Application.hpp>

void init_logger() {
    auto logger = std::make_shared<spdlog::logger>("replay-mod");

    const auto filename = fmt::format("replay/logs/log_{}.txt", utils::get_date_string(std::chrono::system_clock::now()));
    logger->sinks().emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(filename, true));

#if !defined(NDEBUG)
    logger->sinks().emplace_back(std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>());
#endif

    logger->set_level(spdlog::level::trace);
    logger->flush_on(spdlog::level::trace);

    spdlog::set_default_logger(logger);

    spdlog::info("Start logging");
    spdlog::info("Mod version: {}", mod_info::mod_version);
    spdlog::info("Game version: {} ({})", UnityEngine::Application::get_version(), mod_info::get_game_version().to_string());
}
