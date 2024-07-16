from conans import ConanFile, CMake, tools


class LoggingOtelRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"
    
    channel = "stable"

    _gcc_use_from_package = True
    _gcc_package_name = "gcc"
    _gcc_version = "8.2.0"

    @property
    def _gcc_package(self):  return "{}/{}".format(self._gcc_package_name, self._gcc_version)

    _otel_package_name = "opentelemetry-cpp"
    _otel_version = "1.14.2.0"

    @property
    def _otel_package(self): return "{}/{}".format(self._otel_package_name, self._otel_version)

    @property
    def _core_dep_conanuser(self): return "thirdparty"

    def requirements(self):
        self.requires("{}@{}/{}".format(self._otel_package, self._core_dep_conanuser, self.channel))
        self.requires("oatpp/1.3.0")
        self.requires("spdlog/1.14.1")

    def build_requirements(self):
        self.build_requires("cmake/3.17.3@thirdparty/stable")
        if self.settings.compiler == "gcc" and self._gcc_use_from_package:
            self.build_requires("{}@{}/{}".format(self._gcc_package, self._core_dep_conanuser, self.channel))

    def _configure_cmake(self):
        cmake = CMake()

        # It seems this is not correctly passed through
        if self.settings.os == "Linux":
            # This should just work given that CONAN_LIBCXX is defined, but it is not
            # so we force it here.
            libcxx = self.settings.get_safe("compiler.libcxx")
            if str(libcxx) == 'libstdc++':
                cmake.definitions["CMAKE_CXX_FLAGS"] = "-D_GLIBCXX_USE_CXX11_ABI=0"
            elif str(libcxx) == 'libstdc++11':
                cmake.definitions["CMAKE_CXX_FLAGS"] = "-D_GLIBCXX_USE_CXX11_ABI=1"
        else:
            cmake.definitions["CMAKE_CXX_FLAGS"] = "-DNOMINMAX"

        if self.settings.compiler == "gcc" and self._gcc_use_from_package:
            self.output.info("GCC_ROOT={}".format(self.deps_cpp_info[self._gcc_package_name].rootpath))
            cmake.definitions["CMAKE_C_COMPILER"] = os.path.join(
                self.deps_cpp_info[self._gcc_package_name].rootpath,
                "bin",
                "gcc"
            )
            cmake.definitions["CMAKE_CXX_COMPILER"] = os.path.join(
                self.deps_cpp_info[self._gcc_package_name].rootpath,
                "bin",
                "g++"
            )

        # cmake.definitions["CMAKE_INSTALL_RPATH"] = "\$ORIGIN/../lib"
        #cmake.definitions["CMAKE_BUILD_TYPE"] = "Release"

        # cmake.definitions["ZLIB_ROOT"] = self.deps_cpp_info[self._zlib_package_name].rootpath
        # self.output.info("ZLIB_ROOT={}".format(cmake.definitions["ZLIB_ROOT"]))

        # cmake.definitions["OPENSSL_ROOT_DIR"] = self.deps_cpp_info[self._openssl_package_name].rootpath
        # cmake.definitions["OPENSSL_INCLUDE_DIR"] = os.path.join(
        #     self.deps_cpp_info[self._openssl_package_name].rootpath,
        #     "include"
        # )

        # Due to a case mismatch grpc expects OPENSSL_LIBRARIES, where as we provide
        # OpenSSL_LIBRARIES, the same for the includes dir. So this works around that.
        #cmake.definitions["OPENSSL_LIBRARIES"] = "OpenSSL::OpenSSL"

        # cmake.definitions["OPENSSL_USE_STATIC_LIBS"] = self._openssl_shared
        # self.output.info("OPENSSL_ROOT_DIR={}".format(cmake.definitions["OPENSSL_ROOT_DIR"]))

        # # Configure OpenTelemetry-Cpp
        # cmake.definitions["BUILD_TESTING"] = False
        # cmake.definitions["BUILD_BENCHMARK"] = False
        # cmake.definitions["WITH_EXAMPLES"] = False

        cmake.verbose = True
        cmake.configure()
        return cmake

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()
