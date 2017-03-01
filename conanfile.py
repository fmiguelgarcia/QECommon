from conans import ConanFile, CMake 

class QECommonConan(ConanFile):
    name = "QECommon"
    version = "0.1.0"
    settings = "os", "compiler", "build_type", "arch"
    license = "https://www.gnu.org/licenses/lgpl-3.0-standalone.html"
    url = "ssh://miguel@migroslinx.no-ip.org/home/miguel/git/QE/QECommon.git"
    description = """Common header files and abstract classes for Qt Enterprise"""

    def source(self):
        self.run( "git clone %s" % self.url)

    def build(self):
        cmake = CMake( self.settings)
        self.run( "cmake %s/QECommon %s" % (self.conanfile_directory, cmake.command_line))
        self.run( "cmake --build . %s" % cmake.build_config)

    def package(self):
        self.copy( pattern="*.hpp", dst="include/QECommon/", src="QECommon/src")
        self.copy( pattern="LICENSE.LGPLv3", dst="share/QECommon/")
        self.copy( pattern="libQECommon.so*", dst="lib", src="src")
        
    def package_info(self):
        self.cpp_info.libs.extend(["QECommon"])
        self.cpp_info.includedirs.extend(["include/QECommon"])
