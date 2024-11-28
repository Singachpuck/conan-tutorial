# find_package(Boost COMPONENTS date_time REQUIRED)

# add_library(${LIBRARY_NAME})

target_sources(${EXECUTABLE_NAME} PUBLIC context.cpp StateMachine.cpp)

add_subdirectory(exceptions)
add_subdirectory(managers)
add_subdirectory(states)

# target_link_libraries(${LIBRARY_NAME} Boost::date_time)