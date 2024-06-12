cmake_minimum_required(VERSION 3.20)
project(hello)

# set(CMAKE_CXX_STANDARD 20)

find_package(hello REQUIRED)

message("Building with CMake version: ${CMAKE_VERSION}")

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} hello::hello)