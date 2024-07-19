CONAN := /home/dochkas/conan_venv/bin/conan
CMAKE_HOME := /home/dochkas/.conan/data/cmake/3.17.3/thirdparty/stable/package/4db1be536558d833e52e862fd84d64d75c2b3656/cmake-3.17.3-Linux-x86_64/bin/cmake
CC := /home/dochkas/.conan/data/gcc/8.2.0/thirdparty/stable/package/4db1be536558d833e52e862fd84d64d75c2b3656/bin/gcc
CXX := /home/dochkas/.conan/data/gcc/8.2.0/thirdparty/stable/package/4db1be536558d833e52e862fd84d64d75c2b3656/bin/g++

BUILD_DIR := build

SPDLOG_SINK_PATH := /home/dochkas/projects/opentelemetry-cpp-contrib/instrumentation/spdlog/build/install

CMAKE_GENERATE_COMMAND := $(CMAKE_HOME) . -G "Unix Makefiles" -B $(BUILD_DIR) -DCMAKE_TOOLCHAIN_FILE=$(BUILD_DIR)/conan_toolchain.cmake \
	-DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=$(CC) -DCMAKE_CXX_COMPILER=$(CXX) -DCMAKE_PREFIX_PATH=$(SPDLOG_SINK_PATH)

all: clean c-install generate b

examples: clean c-install generate-ex b

roll-dice: clean c-install generate-roll b

c-install:
	$(CONAN) install -pr release -pr linux_x86_64_gcc_8.2.0_CXX03_ABI -if=$(BUILD_DIR) . 

generate:
	$(CMAKE_GENERATE_COMMAND) -DWITH_EXAMPLES=On -DWITH_ROLL_DICE=On

generate-ex:
	$(CMAKE_GENERATE_COMMAND) -DWITH_EXAMPLES=On -DWITH_ROLL_DICE=Off

generate-roll:
	$(CMAKE_GENERATE_COMMAND) -DWITH_EXAMPLES=Off -DWITH_ROLL_DICE=On

b:
	cmake --build ./$(BUILD_DIR)

clean:
	rm -rf build
	mkdir build

run-examples:
	./build/app/logging_tutorial

run-dice:
	./build/app/roll_dice/dice-server