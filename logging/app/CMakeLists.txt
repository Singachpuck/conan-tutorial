if (WITH_EXAMPLES)
    add_executable(${LOGGING_EXECUTABLE_NAME} logging_tutorial.cc)
    target_link_libraries(${LOGGING_EXECUTABLE_NAME} opentelemetry-cpp::opentelemetry-cpp spdlog::spdlog
        opentelemetry_spdlog_sink::opentelemetry_spdlog_sink)

    add_executable(${MDC_EXECUTABLE_NAME} mdc_example.cc)
    target_link_libraries(${MDC_EXECUTABLE_NAME} opentelemetry-cpp::opentelemetry-cpp Boost::log)
endif (WITH_EXAMPLES)

if (WITH_ROLL_DICE)
    add_subdirectory(roll_dice)
endif (WITH_ROLL_DICE)