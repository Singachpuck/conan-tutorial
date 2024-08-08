# find_package(Boost COMPONENTS date_time REQUIRED)

# add_library(${LIBRARY_NAME})

target_sources(${EXECUTABLE_NAME} PUBLIC StateMachine.cpp)

add_subdirectory(states)

# target_link_libraries(${LIBRARY_NAME} Boost::date_time)