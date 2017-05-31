# Requirements 
include( ${CMAKE_SOURCE_DIR}/tools/cmake/common.cmake)
find_package( Qt5Sql REQUIRED)

set( QECommon_MAYOR_VERSION 1)
set( QECommon_MINOR_VERSION 0)
set( QECommon_BUILD_VERSION 0)

# Source
set( QECommon_SRCS 
	Common.cpp
	Exception.cpp 
	Gadget.cpp
	FutureBase.cpp
	FutureData.cpp
	Future.cpp
	DBConnectionLockGuard.cpp
	DBConnectionPool.cpp
)
add_definitions( -DBUILD_QECOMMON_LIB)

# Link
add_library( QECommon SHARED ${QECommon_SRCS})
target_link_libraries( QECommon 
   Qt5::Core Qt5::Sql ${CONAN_LIBS})
set_target_properties( QECommon PROPERTIES 
	VERSION ${QECommon_MAYOR_VERSION}.${QECommon_MINOR_VERSION}.${QECommon_BUILD_VERSION}
	SOVERSION ${QECommon_MAYOR_VERSION})
target_compile_features( QECommon 
   PUBLIC cxx_auto_type cxx_lambdas cxx_nullptr)
