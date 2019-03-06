cmake_minimum_required (VERSION 3.8)

set_property(GLOBAL PROPERTY USE_FOLDERS ON) 

add_definitions(/DINTERCEPT_HOST_DLL=1)
add_definitions(/DNOMINMAX)

if (NOT CMAKE_BUILD_TYPE AND CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "No build type selected, default to Debug")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

option(DEVEL "DEVEL" ON)
option(USE_STATIC_LINKING "USE_STATIC_LINKING" ON)

include_directories("common")
include_directories("controller")
include_directories("loader")
include_directories("invoker")
include_directories("extensions")
include_directories("../client/headers")
include_directories("intercept_dll")

if(DEVEL)
    add_definitions(-DDEVEL)
endif()

include_directories(${CMAKE_CURRENT_BINARY_DIR}/common)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/controller)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/loader)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/invoker)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/extensions)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/intercept_dll)


set(GLOBAL_SOURCES ${GLOBAL_RC})


add_subdirectory(common)
add_subdirectory(controller)
add_subdirectory(loader)
add_subdirectory(invoker)
add_subdirectory(extensions)
add_subdirectory(intercept_dll)



message("Build Type: ${CMAKE_BUILD_TYPE}")

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message("clang is unsupported for usage with Arma")
endif()
