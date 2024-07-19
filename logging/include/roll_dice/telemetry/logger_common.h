#ifndef ROLL_DICE_LOGGER_COMMON
#define ROLL_DICE_LOGGER_COMMON

#include "spdlog/spdlog.h"
#include "opentelemetry/instrumentation/spdlog/sink.h"


std::shared_ptr<spdlog::logger> logger = nullptr;

inline void initLogger()
{
#ifdef WITH_OTEL_LOGS
    auto otel_sink = std::make_shared<spdlog::sinks::opentelemetry_sink_mt>();
    otel_sink->set_level(spdlog::level::trace);
    logger = std::make_shared<spdlog::logger>("roll-dice-logger", otel_sink);
#else
    logger = std::make_shared<spdlog::logger>("roll-dice-logger");
#endif
    logger->set_level(spdlog::level::trace);
}

inline std::shared_ptr<spdlog::logger> getLogger()
{
    return logger;
}

#endif