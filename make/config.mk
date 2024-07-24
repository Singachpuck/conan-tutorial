ifeq ($(OS), Windows_NT)

include windows.mk 

else
ifeq ($(shell uname), Linux)

include linux.mk

else

$(error OS is not recognized)

endif
endif

CMAKE_GENERATE_COMMAND := $(CMAKE_HOME) . -G "$(CMAKE_GENERATOR)" -B $(BUILD_DIR) -DCMAKE_TOOLCHAIN_FILE=$(BUILD_DIR)/conan_toolchain.cmake \
	-DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=$(CC) -DCMAKE_CXX_COMPILER=$(CXX)