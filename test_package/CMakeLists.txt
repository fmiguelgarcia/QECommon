project(QAnnotationTest)
cmake_minimum_required(VERSION 3.0.0)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
find_package( Qt5Core REQUIRED)

set( CMAKE_AUTOMOC ON)
set( CMAKE_AUTOUIC ON)
set( CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable( packageTest main.cpp)
target_link_libraries( packageTest Qt5::Core ${CONAN_LIBS})
set_property( TARGET packageTest  PROPERTY CXX_STANDARD 11)
