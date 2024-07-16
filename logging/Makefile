CONAN := /home/dochkas/conan_venv/bin/conan
CC := /home/dochkas/.conan/data/gcc/8.2.0/thirdparty/stable/package/4db1be536558d833e52e862fd84d64d75c2b3656/bin/gcc
CXX := /home/dochkas/.conan/data/gcc/8.2.0/thirdparty/stable/package/4db1be536558d833e52e862fd84d64d75c2b3656/bin/g++

BUILD_DIR := build

SPDLOG_SINK_PATH=/home/dochkas/projects/opentelemetry-cpp-contrib/instrumentation/spdlog/build/install

all: clean c-install generate b

c-install:
	$(CONAN) install -pr release -pr linux_x86_64_gcc_8.2.0_CXX03_ABI -if=$(BUILD_DIR) . 

generate:
	cmake . -G "Unix Makefiles" -B $(BUILD_DIR) -DCMAKE_TOOLCHAIN_FILE=$(BUILD_DIR)/conan_toolchain.cmake \
	-DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=$(CC) -DCMAKE_CXX_COMPILER=$(CXX) -DCMAKE_PREFIX_PATH=$(SPDLOG_SINK_PATH)

b:
	cmake --build ./$(BUILD_DIR)

clean:
	rm -rf build
	mkdir build

cd-oatpp:
	cd oatpp

build-oatpp:
	cd oatpp; \
	cmake . -B $(BUILD_DIR) -DCMAKE_INSTALL_PREFIX=bin ;
	# cmake --build ./build --target install

build-spdlog:
	cd /home/dochkas/projects/opentelemetry-cpp-contrib/instrumentation/spdlog; \
	cmake . -B $(BUILD_DIR) -DCMAKE_INSTALL_PREFIX=bin -D "CMAKE_PREFIX_PATH=/home/dochkas/.conan/data/fmt/10.2.1/_/_/package/a3a15a7f5a0446bc5fe58079f519284e91f0cdc0;/home/dochkas/.conan/data/spdlog/1.14.1/_/_/package/1d6963f8e6c0dd7d58dbad139be8192b111a8499" \
	-DCMAKE_C_COMPILER=$(CC) -DCMAKE_CXX_COMPILER=$(CXX) ;
	cmake --build ./build