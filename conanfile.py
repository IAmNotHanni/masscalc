from conans import ConanFile, CMake

class MasscalcConan(ConanFile):
    settings = (
        "os",
        "compiler",
        "build_type",
        "arch"
    )

    requires = (
        "glfw/3.3.7",
        "spdlog/1.10.0",
    )

    options = {
        "build_benchmarks": [True, False],
        "build_tests": [True, False],
    }
    default_options = {
        "build_benchmarks": False,
        "build_tests": False,
    }

    generators = "cmake"

    def configure(self):
        if self.settings.os == "Linux" and self.settings.compiler.libcxx == "libstdc++":
            raise Exception("Masscalc is not compatible with libstdc++. "
                            "Please change the 'compiler.libcxx'-setting "
                            "(e.g. to libstdc++11).")

    def requirements(self):
        if self.options.build_benchmarks:
            self.requires("benchmark/1.6.2")
        if self.options.build_tests:
            self.requires("gtest/1.12.1")

    def imports(self):
        # Copies all dll files from packages bin folder to my "bin" folder (win)
        self.copy("*.dll", dst="bin", src="bin")
        # Copies all dylib files from packages lib folder to my "lib" folder (macosx)
        self.copy("*.dylib*", dst="lib", src="lib")
        # Copies all so files from packages lib folder to my "lib" folder (linux)
        self.copy("*.so*", dst="lib", src="lib")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
