cmake_minimum_required(VERSION 3.15)
project(logging_tutorial VERSION 1.0.0 LANGUAGES CXX)

set(EXECUTABLE_NAME ${PROJECT_NAME})

find_package(opentelemetry-cpp REQUIRED)
find_package(oatpp REQUIRED)

add_subdirectory(app)