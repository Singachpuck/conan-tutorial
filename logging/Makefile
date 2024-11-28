-include config.mk

SPDLOG_SINK_PATH := /home/dochkas/projects/opentelemetry-cpp-contrib/instrumentation/spdlog/build/install

CMAKE_GENERATE_COMMAND +=  -DCMAKE_PREFIX_PATH=$(SPDLOG_SINK_PATH)

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
	./build/app/mdc_example

run-dice:
	./build/app/roll_dice/dice-server