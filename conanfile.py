from conans import ConanFile, CMake


class BitprimconsensusConan(ConanFile):
    name = "bitprim-consensus"
    version = "0.1"
    license = "http://www.boost.org/users/license.html"
    url = "https://github.com/bitprim/bitprim-consensus"
    description = "Bitcoin Consensus Library"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = "shared=False"
    generators = "cmake"

    # exports_sources = "src/*", "CMakeLists.txt", "cmake/*"
    exports_sources = "src/*", "CMakeLists.txt", "cmake/*", "bitprim-consensusConfig.cmake.in", "include/*"

    package_files = "build/lbitprim-consensus.a"

    # def build(self):
    #     cmake = CMake(self)
    #     cmake.configure(source_dir=self.conan_directory)
    #     cmake.build()

    # def package(self):
    #     self.copy("*.h", dst="include", src="src")
    #     self.copy("*.lib", dst="lib", keep_path=False)
    #     self.copy("*.dll", dst="bin", keep_path=False)
    #     self.copy("*.dylib*", dst="lib", keep_path=False)
    #     self.copy("*.so", dst="lib", keep_path=False)
    #     self.copy("*.a", dst="lib", keep_path=False)
    #
    # def package_info(self):
    #     self.cpp_info.libs = ["bitprim-consensus"]

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_dir=self.conanfile_directory)
        cmake.build()

    def imports(self):
        self.copy("*.h", "", "include")

    def package(self):
        self.copy("*.h", dst="include", src="include")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.includedirs = ['include']
        self.cpp_info.libs = ["bitprim-consensus"]

