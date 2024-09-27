CONAN := $(ANSYS_CONAN_VENV_PATH)/bin/conan
CMAKE_HOME := $(CONAN_USER_HOME)/.conan/data/cmake/3.17.3/thirdparty/stable/package/4db1be536558d833e52e862fd84d64d75c2b3656/cmake-3.17.3-Linux-x86_64/bin/cmake
CMAKE_GENERATOR := Unix Makefiles
CC := $(CONAN_USER_HOME)/.conan/data/gcc/8.2.0/thirdparty/stable/package/4db1be536558d833e52e862fd84d64d75c2b3656/bin/gcc
CXX := $(CONAN_USER_HOME)/.conan/data/gcc/8.2.0/thirdparty/stable/package/4db1be536558d833e52e862fd84d64d75c2b3656/bin/g++
PROTOC := ${CONAN_USER_HOME}/.conan/data/protoc/3.19.6.1/thirdparty/stable/package/e7386aea233479b9c19847662774fd68da40b975/bin/protoc

GRPC_PLUGIN := $(CONAN_USER_HOME)/.conan/data/grpc_plugins/1.46.7.9/thirdparty/stable/package/1036933dfdff90461d4bf4154f59e6aa78392d87/bin/grpc_cpp_plugin
BUILD_DIR := build