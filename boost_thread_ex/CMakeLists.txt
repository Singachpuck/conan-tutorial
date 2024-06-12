cmake_minimum_required(VERSION 3.20)
project(echo_server)

find_package(Boost REQUIRED)

message("Building with CMake version: ${CMAKE_VERSION}")

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} Boost::thread) 