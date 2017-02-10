from conans import ConanFile, CMake 

class QECommonConan(ConanFile):
    name = "QECommon"
    version = "0.1.0"
    settings = "os", "compiler", "build_type", "arch"
    license = "LGPL 2.0"

    def source(self):
        self.run("git clone ssh://miguel@migroslinx.no-ip.org/home/miguel/git/QE/QECommon.git") 

    def package(self):
        self.copy( pattern="*.hpp", dst="include/QECommon/", src="/src")
        
    def package_info(self):
        self.cpp_info.includedirs.extend(["include/QECommon"])

