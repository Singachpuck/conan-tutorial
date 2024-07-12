# Define your project's source files
set(SOURCES
    roll_dice.cc  # Add your source files here
)

# Create an executable target
add_executable(dice-server ${SOURCES})

# set(OATPP_ROOT ../oatpp)
# find_library(OATPP_LIB NAMES liboatpp.a HINTS "${OATPP_ROOT}/build/src/" NO_DEFAULT_PATH)

if (NOT oatpp_VERSION_STRING)
  message(SEND_ERROR "Did not find oatpp library.")
endif()

if (NOT opentelemetry-cpp_VERSION_STRING)
  message(SEND_ERROR "Did not find oatpp library.")
endif()

#set the path to the directory containing "oatpp" package configuration files
target_link_libraries(dice-server PRIVATE opentelemetry-cpp::opentelemetry-cpp oatpp::oatpp)