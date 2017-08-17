from conans import ConanFile, CMake

def option_on_off(option):
    return "ON" if option else "OFF"

class BitprimConsensusConan(ConanFile):
    name = "bitprim-consensus"
    version = "0.1"
    license = "http://www.boost.org/users/license.html"
    url = "https://github.com/bitprim/bitprim-consensus"
    description = "Bitcoin Consensus Library"
    settings = "os", "compiler", "build_type", "arch"

    # options = {"shared": [True, False]}
    # default_options = "shared=False"

    options = {"shared": [True, False],
               "fPIC": [True, False],
               "with_tests": [True, False],
               "with_java": [True, False],
               "with_python": [True, False],
    }

    default_options = "shared=False", \
        "fPIC=True", \
        "with_tests=True", \
        "with_java=False", \
        "with_python=False"

# option(USE_CONAN "Use Conan Build Tool." OFF)
# option(WITH_TESTS "Compile with unit tests." ON)
# option(WITH_JAVA "Compile the Java bindings." OFF)
# option(WITH_PYTHON "Compile the Python bindings." OFF)
# option(ENABLE_SHARED "" OFF)


    generators = "cmake"
    build_policy = "missing"

    exports_sources = "src/*", "CMakeLists.txt", "cmake/*", "bitprim-consensusConfig.cmake.in", "include/*", "test/*"

    package_files = "build/lbitprim-consensus.a"

    requires = (("bitprim-conan-boost/1.64.0@bitprim/stable"),
                ("secp256k1/0.1@bitprim/testing"),
                ("bitprim-core/0.1@bitprim/testing"))

    def build(self):
        cmake = CMake(self)

        cmake.definitions["USE_CONAN"] = "ON"
        cmake.definitions["CMAKE_VERBOSE_MAKEFILE"] = "ON"
        cmake.definitions["ENABLE_SHARED"] = option_on_off(self.options.shared)
        cmake.definitions["ENABLE_POSITION_INDEPENDENT_CODE"] = option_on_off(self.options.fPIC)
        cmake.definitions["WITH_TESTS"] = option_on_off(self.options.with_tests)
        cmake.definitions["WITH_JAVA"] = option_on_off(self.options.with_java)
        cmake.definitions["WITH_PYTHON"] = option_on_off(self.options.with_python)
        
        cmake.configure(source_dir=self.conanfile_directory)
        cmake.build()

    def imports(self):
        self.copy("*.h", "", "include")

    def package(self):
        self.copy("*.h", dst="include", src="include")
        self.copy("*.hpp", dst="include", src="include")
        self.copy("*.ipp", dst="include", src="include")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)


    def package_info(self):
        self.cpp_info.includedirs = ['include']
        self.cpp_info.libs = ["bitprim-consensus"]
