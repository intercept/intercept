cmake_minimum_required (VERSION 3.8)
project (Intercept)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)
include(${PROJECT_SOURCE_DIR}/CMakeModules/cxx_compiler_functions.cmake)

if (NOT CMAKE_VERSION VERSION_LESS "3.13")
    # CMP0077: option() honors normal variables
    # https://cmake.org/cmake/help/latest/policy/CMP0077.html
    cmake_policy(SET CMP0077 NEW)
endif()

option(USE_64BIT_BUILD "USE_64BIT_BUILD" OFF)
option(USE_STATIC_LINKING "USE_STATIC_LINKING" ON)

if(USE_STATIC_LINKING)
    message("WARNING: Linking statically")
    set(INTERCEPT_LINK_TYPE "static")
else()
    message("WARNING: Linking dynamically")
    set(INTERCEPT_LINK_TYPE "dynamic")
endif()

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC" AND "${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
    set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /std:c++latest" )
    set( USE_64BIT_BUILD ON)
elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC")
    set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /std:c++latest" )
endif()

message("GENERATOR USED: '${CMAKE_GENERATOR}'")
message("COMPILER USED: '${CMAKE_CXX_COMPILER_ID}'")

set(CMAKE_CL_64 ${USE_64BIT_BUILD})

if(USE_64BIT_BUILD)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build/win64/")
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build/win32/")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


SET(CMAKE_INCLUDE_CURRENT_DIR ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

add_subdirectory(src/host)
add_subdirectory(src/client)

#set(INTERCEPT_EXAMPLE_SRC "Z:/intercept-examples")
if(INTERCEPT_EXAMPLE_SRC)
    set(INTERCEPT_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/src/client/headers")

    add_subdirectory("${INTERCEPT_EXAMPLE_SRC}/src" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
endif()
