cmake_minimum_required(VERSION 3.15)
project(linkholderapp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


set(EXECUTABLE_NAME ${PROJECT_NAME})

find_package(Boost REQUIRED COMPONENT date_time)
find_package(linkholderlib REQUIRED)

add_subdirectory(app) 
add_subdirectory(src)
add_subdirectory(include)