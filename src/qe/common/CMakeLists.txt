# Requirements 
include( ${CMAKE_SOURCE_DIR}/tools/cmake/common.cmake)

set( QECommon_MAYOR_VERSION 0)
set( QECommon_MINOR_VERSION 1)
set( QECommon_BUILD_VERSION 0)

# Source
set( QECommon_SRCS Exception.cpp Gadget.cpp)

# Link
add_library( QECommon SHARED ${QECommon_SRCS})
target_link_libraries( QECommon Qt5::Core ${CONAN_LIBS}) 
set_target_properties( QECommon PROPERTIES 
	VERSION ${QECommon_MAYOR_VERSION}.${QECommon_MINOR_VERSION}.${QECommon_BUILD_VERSION}
	SOVERSION ${QECommon_MAYOR_VERSION})
target_compile_features( QECommon PUBLIC cxx_auto_type cxx_lambdas cxx_nullptr)
