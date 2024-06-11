cmake_minimum_required(VERSION 3.15)
project(echo_server)

find_package(zlib REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ZLIB::ZLIB) 