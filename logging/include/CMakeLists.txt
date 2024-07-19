
if (WITH_EXAMPLES)
    target_include_directories(${EXECUTABLE_NAME} PUBLIC
        ${CMAKE_BINARY_DIR}/configured_files/include)
endif (WITH_EXAMPLES)

if (WITH_ROLL_DICE)
    add_subdirectory(roll_dice)
endif (WITH_ROLL_DICE)