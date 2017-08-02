from conans import ConanFile, CMake 
import os 

class QECommonConan(ConanFile):
    name = "QECommon"
    version = "1.0.0"
    settings = "os", "compiler", "build_type", "arch"
    license = "https://www.gnu.org/licenses/lgpl-3.0-standalone.html"
    url = "https://github.com/fmiguelgarcia/QECommon.git"
    generators = "cmake"
    description = "Common header files and abstract classes for QE"
    exports_sources = ["src/*", "test/*", "tools/*", "CMakeLists.txt", "!.*.swp"]
    options = { "qt_version": "ANY", "use_std_optional": [True ,False]}
    default_options = "use_std_optional=False"

    def configure(self):
        self.options.qt_version = os.popen("qmake -query QT_VERSION").read().strip()
        self.output.info("Configure Qt Version: %s" % self.options.qt_version)

    def requirements(self):
        if self.settings.os == "Windows":
            self.requires( "Boost/1.64.0@fmiguelgarcia/stable")

    def build(self):
        cmake = CMake( self)
        cmake.definitions[ "QE_USE_STD_OPTIONAL"] = self.options.use_std_optional
        cmake.configure()
        cmake.build()

    def package(self):
        # Headers and 
        self.copy( pattern="*.hpp", dst="include", src="src")
        self.copy( pattern="LICENSE.LGPLv3", dst="share/qe/common/")

        if self.settings.compiler == "Visual Studio":
            libNames = ["QECommon", "libQECommon"]
            for libName in libNames:
                filePattern = "**/" + libName + ".lib"
                self.copy( filePattern, dst="lib", src="src/qe/common", keep_path=False)

            libExts = [".dll", ".pdb"]
            for libName in libNames:
                for libExt in libExts:
                    filePattern = "**/" + libName + libExt
                    self.copy( pattern=filePattern, dst="bin", src="src/qe/common", keep_path=False)

        else:
            self.copy( "libQECommon.so*", dst="lib", src="src/qe/common", links=True, keep_path=False)
        
    def package_info(self):
        self.cpp_info.libs.extend(["QECommon"])
