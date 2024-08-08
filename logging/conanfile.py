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

    _oatpp_package_name = "oatpp"
    _oatpp_version = "1.3.0"

    @property
    def _oatpp_package(self): return "{}/{}".format(self._oatpp_package_name, self._oatpp_version)

    _spdlog_package_name = "spdlog"
    _spdlog_version = "1.14.1"
    
    @property
    def _spdlog_package(self): return "{}/{}".format(self._spdlog_package_name, self._spdlog_version)

    _boost_package_name = "boost"
    _boost_version = "1.85.0"

    @property
    def _boost_package(self): return "{}/{}".format(self._boost_package_name, self._boost_version)

    _nlohmann_package_name = "nlohmann_json"
    _nlohmann_version = "3.11.3"

    @property
    def _nlohmann_package(self): return "{}/{}".format(self._nlohmann_package_name, self._nlohmann_version)

    _cmake_package_name = "cmake"
    _cmake_version = "3.17.3"

    @property
    def _cmake_package(self): return "{}/{}".format(self._cmake_package_name, self._cmake_version)

    @property
    def _core_dep_conanuser(self): return "thirdparty"


    def requirements(self):
        self.requires("{}@{}/{}".format(self._otel_package, self._core_dep_conanuser, self.channel))
        self.requires("zlib/1.2.13@thirdparty/stable", override=True)
        self.requires(self._oatpp_package)
        self.requires(self._spdlog_package)
        self.requires(self._boost_package)
        self.requires(self._nlohmann_package)

    def build_requirements(self):
        self.build_requires("{}@{}/{}".format(self._cmake_package, self._core_dep_conanuser, self.channel))
