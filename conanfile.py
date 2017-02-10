from conans import ConanFile, CMake 

class QECommonConan(ConanFile):
    name = "QECommon"
    version = "0.1.0"
    settings = "os", "compiler", "build_type", "arch"
    license = "https://www.gnu.org/licenses/lgpl-3.0-standalone.html"
    exports = "*"

    def package(self):
        self.copy( pattern="*.hpp", dst="include/QECommon/", src="src")
        self.copy( pattern="LICENSE.LGPLv3", dst="share/QECommon/")
        
    def package_info(self):
        self.cpp_info.includedirs.extend(["include/QECommon"])
