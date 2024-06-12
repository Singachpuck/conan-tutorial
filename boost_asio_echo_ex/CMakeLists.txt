cmake_minimum_required(VERSION 3.20)
project(asio_test)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost REQUIRED)

message("Building with CMake version: ${CMAKE_VERSION}")

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} boost::boost)

if(MINGW)
  target_link_libraries(${PROJECT_NAME} ws2_32 wsock32)
endif()