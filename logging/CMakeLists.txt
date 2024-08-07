cmake_minimum_required(VERSION 3.15)
project(logging_tutorial VERSION 1.0.0 LANGUAGES CXX)

option(WITH_EXAMPLES "Should build Logging examples?" On)
option(WITH_ROLL_DICE "Should build Roll Dice server?" Off)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=unused-function")

if (WITH_EXAMPLES)
    set(LOGGING_EXECUTABLE_NAME "logging_tutorial")
    set(MDC_EXECUTABLE_NAME "mdc_example")
endif (WITH_EXAMPLES)

if (WITH_ROLL_DICE)
    set(ROLL_DICE_EXECUTABLE dice-server)
endif (WITH_ROLL_DICE)

find_package(Boost REQUIRED COMPONENTS log)
find_package(oatpp REQUIRED)
find_package(spdlog REQUIRED)
find_package(opentelemetry-cpp REQUIRED)
find_package(opentelemetry_spdlog_sink REQUIRED)

add_subdirectory(configured)
add_subdirectory(app)
add_subdirectory(include)