cmake_minimum_required(VERSION 3.15)
project(logging_tutorial VERSION 1.0.0 LANGUAGES CXX)

set(EXECUTABLE_NAME ${PROJECT_NAME})
set(ROLL_DICE_EXECUTABLE dice-server)

find_package(oatpp REQUIRED)
find_package(spdlog REQUIRED)
find_package(opentelemetry-cpp REQUIRED)
find_package(opentelemetry_spdlog_sink REQUIRED)

add_subdirectory(app)
add_subdirectory(include)