if (WITH_EXAMPLES)
    add_executable(${EXECUTABLE_NAME} main.cc)
    target_link_libraries(${EXECUTABLE_NAME} opentelemetry-cpp::opentelemetry-cpp spdlog::spdlog
        opentelemetry_spdlog_sink::opentelemetry_spdlog_sink)
endif (WITH_EXAMPLES)

if (WITH_ROLL_DICE)
    add_subdirectory(roll_dice)
endif (WITH_ROLL_DICE)