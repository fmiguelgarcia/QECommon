from conans import ConanFile, CMake 

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
        cmake = CMake( self)
        cmake.configure()
        cmake.build()

    def package(self):
        self.copy( pattern="*.hpp", dst="include/qe/common/", src="src/qe/common")
        self.copy( pattern="LICENSE.LGPLv3", dst="share/qe/common/")
        self.copy( pattern="libQECommon.so*", dst="lib", src="src/qe/common",
                links=True)
        if self.settings.os == "Windows":
            libNames = ["QECommon", "libQECommon"]
            libExts = [".dll", ".lib", ".dll.a", ".pdb"]
            for libName in libNames:
                for libExt in libExts:
                    filePattern = "**/" + libName + libExt
                    self.copy( pattern=filePattern, dst="lib", src="src/qe/common", keep_path=False)
        
    def package_info(self):
        self.cpp_info.libs.extend(["QECommon"])
