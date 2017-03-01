# Requirements 
find_package( Qt5Core REQUIRED)
set( CMAKE_AUTOMOC ON)
set( CMAKE_INCLUDE_CURRENT_DIR ON)

# Source
set( QECommon_MAYOR_VERSION 0)
set( QECommon_MINOR_VERSION 1)
set( QECommon_BUILD_VERSION 0)

set( QECommon_SRCS
	QEGadget.cpp
	QES11n.cpp) 

# Link
add_library( QECommon SHARED ${QECommon_SRCS})
target_link_libraries( QECommon Qt5::Core ${CONAN_LIBS}) 
set_target_properties( QECommon PROPERTIES 
	VERSION ${QECommon_MAYOR_VERSION}.${QECommon_MINOR_VERSION}.${QECommon_BUILD_VERSION}
	SOVERSION ${QECommon_MAYOR_VERSION}
	CXX_STANDARD 11)
