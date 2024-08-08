from conan import ConanFile


class CompressorRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    _boost_package_name = "boost"
    _boost_version = "1.85.0"

    @property
    def _boost_package(self): return "{}/{}".format(self._boost_package_name, self._boost_version)

    _linkholderlib_package_name = "linkholderlib"
    _linkholderlib_version = "1.0"

    @property
    def _linkholderlib_package(self): return "{}/{}".format(self._linkholderlib_package_name, self._linkholderlib_version)

    _cmake_package_name = "cmake"
    _cmake_version = "3.22.6"

    @property
    def _cmake_package(self): return "{}/{}".format(self._cmake_package_name, self._cmake_version)

    def configure(self):
        if self.settings.compiler == "gcc":
            self.options[self._boost_package_name].without_url = True

    def requirements(self):
        self.requires(self._boost_package)
        self.requires(self._linkholderlib_package)

    def build_requirements(self):
        self.tool_requires(self._cmake_package)