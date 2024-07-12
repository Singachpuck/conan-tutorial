add_executable(${EXECUTABLE_NAME} main.cc)

target_link_libraries(${EXECUTABLE_NAME} opentelemetry-cpp::opentelemetry-cpp)

add_subdirectory(roll_dice)