set(SOURCES roll_dice.cc)

add_executable(${ROLL_DICE_EXECUTABLE} ${SOURCES})

target_compile_definitions(${ROLL_DICE_EXECUTABLE} PUBLIC WITH_OTEL_LOGS WITH_TRACES)

if (NOT oatpp_VERSION_STRING)
  message(SEND_ERROR "Did not find oatpp library.")
endif()

if (NOT opentelemetry-cpp_VERSION_STRING)
  message(SEND_ERROR "Did not find otel library.")
endif()

target_link_libraries(${ROLL_DICE_EXECUTABLE} PRIVATE opentelemetry-cpp::opentelemetry-cpp oatpp::oatpp
  spdlog::spdlog opentelemetry_spdlog_sink::opentelemetry_spdlog_sink)