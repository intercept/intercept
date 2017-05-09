cmake_minimum_required (VERSION 3.0)
project (Intercept)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)
include(${PROJECT_SOURCE_DIR}/CMakeModules/cxx_compiler_functions.cmake)

option(USE_STATIC_LINKING "USE_STATIC_LINKING" ON)

if(USE_STATIC_LINKING) 
	message("WARNING: Linking statically")
	set(INTERCEPT_LINK_TYPE "static")
else()
	message("WARNING: Linking dynamically")
	set(INTERCEPT_LINK_TYPE "dynamic")
endif()

message("GENERATOR USED: '${CMAKE_GENERATOR}'")

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build/win32/")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_INCLUDE_CURRENT_DIR ON) 
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(src/host)
add_subdirectory(src/client)

#set(INTERCEPT_EXAMPLE_SRC "Z:/intercept-examples")
if(INTERCEPT_EXAMPLE_SRC)
    set(INTERCEPT_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/src/client/headers")

    add_subdirectory("${INTERCEPT_EXAMPLE_SRC}/src" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
endif()
