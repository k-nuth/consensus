# Copyright (c) 2016-2020 Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

import os
from conans import CMake
from kthbuild import option_on_off, march_conan_manip, pass_march_to_compiler
from kthbuild import KnuthConanFile

class KnuthConsensusConan(KnuthConanFile):
    def recipe_dir(self):
        return os.path.dirname(os.path.abspath(__file__))

    name = "consensus"
    # version = get_version()
    license = "http://www.boost.org/users/license.html"
    url = "https://github.com/k-nuth/consensus"
    description = "Bitcoin Consensus Library"
    settings = "os", "compiler", "build_type", "arch"

    options = {"shared": [True, False],
               "fPIC": [True, False],
               "tests": [True, False],
               "currency": ['BCH', 'BTC', 'LTC'],
               "microarchitecture": "ANY",
               "fix_march": [True, False],
               "march_id": "ANY",
               "verbose": [True, False],
               "cxxflags": "ANY",
               "cflags": "ANY",
               "glibcxx_supports_cxx11_abi": "ANY",
               "cmake_export_compile_commands": [True, False],
    }

    #    "with_java": [True, False],
    #    "with_python": [True, False],

    default_options = "shared=False", \
        "fPIC=True", \
        "tests=False", \
        "currency=BCH", \
        "microarchitecture=_DUMMY_",  \
        "fix_march=False", \
        "march_id=_DUMMY_",  \
        "verbose=False", \
        "cxxflags=_DUMMY_", \
        "cflags=_DUMMY_", \
        "glibcxx_supports_cxx11_abi=_DUMMY_", \
        "cmake_export_compile_commands=False"

        # "with_png=False", \
        # "with_java=False", \
        # "with_python=False", \

    generators = "cmake"
    exports = "conan_*", "ci_utils/*"
    exports_sources = "src/*", "CMakeLists.txt", "cmake/*", "kth-consensusConfig.cmake.in", "knuthbuildinfo.cmake", "include/*", "test/*"
    package_files = "build/lkth-consensus.a"
    build_policy = "missing"


    def requirements(self):
        self.requires("boost/1.72.0@kth/stable")
        self.requires("secp256k1/0.X@%s/%s" % (self.user, self.channel))

    def config_options(self):
        KnuthConanFile.config_options(self)

    def configure(self):
        KnuthConanFile.configure(self)

        # "enable_experimental=False", \
        # "enable_endomorphism=False", \
        # "enable_ecmult_static_precomputation=True", \
        # "enable_module_ecdh=False", \
        # "enable_module_schnorr=True", \
        # "enable_module_recovery=True", \
        # "enable_module_multiset=True", \
        
        if self.options.currency == 'BCH':
            self.options["secp256k1"].enable_module_schnorr = True
        else:
            self.options["secp256k1"].enable_module_schnorr = False

    def package_id(self):
        KnuthConanFile.package_id(self)

    def build(self):
        cmake = self.cmake_basis()
        # cmake.definitions["WITH_TESTS"] = option_on_off(self.options.with_tests)
        # cmake.definitions["WITH_JAVA"] = option_on_off(self.options.with_java)
        # cmake.definitions["WITH_PYTHON"] = option_on_off(self.options.with_python)

        cmake.configure(source_dir=self.source_folder)
        cmake.build()

        if self.options.tests:
            cmake.test()
            # cmake.test(target="tests")

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
        self.cpp_info.libs = ["kth-consensus"]
