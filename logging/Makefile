CONAN := /home/dochkas/conan_venv/bin/conan
CC := /home/dochkas/.conan/data/gcc/8.2.0/thirdparty/stable/package/4db1be536558d833e52e862fd84d64d75c2b3656/bin/gcc
CXX := /home/dochkas/.conan/data/gcc/8.2.0/thirdparty/stable/package/4db1be536558d833e52e862fd84d64d75c2b3656/bin/g++

BUILD_DIR := build

all: clean c-install generate b

c-install:
	$(CONAN) install -pr release -pr linux_x86_64_gcc_8.2.0_CXX03_ABI -if=$(BUILD_DIR) . 

generate:
	cmake . -G "Unix Makefiles" -B $(BUILD_DIR) -DCMAKE_TOOLCHAIN_FILE=$(BUILD_DIR)/conan_toolchain.cmake \
	-DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=$(CC) -DCMAKE_CXX_COMPILER=$(CXX)

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
