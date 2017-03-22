from conans import ConanFile, CMake 
from conans.tools import os_info
import multiprocessing

class QECommonConan(ConanFile):
    name = "QECommon"
    version = "0.1.0"
    settings = "os", "compiler", "build_type", "arch"
    license = "https://www.gnu.org/licenses/lgpl-3.0-standalone.html"
    url = "https://github.com/fmiguelgarcia/QECommon.git"
    generators = "cmake"
    description = "Common header files and abstract classes for QE"
    exports_sources = ["src/*", "test/*", "tools/*", "CMakeLists.txt"]

    def build(self):
        cmake = CMake( self.settings)
        self.run( "cmake %s %s" % (self.conanfile_directory, cmake.command_line))
        self.run( "cmake --build . %s" % (cmake.build_config,
            ("-- -j %d " % multiprocessing.cpu_count()) if os_info.is_linux else ""))

    def package(self):
        self.copy( pattern="*.hpp", dst="include/qe/common/", src="src/qe/common")
        self.copy( pattern="LICENSE.LGPLv3", dst="share/qe/common/")
        self.copy( pattern="libQECommon.so*", dst="lib", src="src/qe/common",
                links=True)
        
    def package_info(self):
        self.cpp_info.libs.extend(["QECommon"])
