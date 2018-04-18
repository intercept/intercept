cmake_minimum_required (VERSION 3.8)

set_property(GLOBAL PROPERTY USE_FOLDERS ON) 

add_definitions(/DINTERCEPT_HOST_DLL=1)
add_definitions(/DNOMINMAX)

if (NOT CMAKE_BUILD_TYPE AND CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "No build type selected, default to Debug")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

option(USE_STATIC_LINKING "USE_STATIC_LINKING" ON)


if(CMAKE_COMPILER_IS_GNUCXX)
    #remove -s to enable debug symbols. Also maybe add -g or -g3
    SET(CMAKE_CXX_FLAGS "-std=c++1z -march=i686 -m32 -O2 -s -fPIC -fpermissive -pthread")
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
    set(CMAKE_SHARED_LINKER_FLAGS "-static -static-libgcc -static-libstdc++ -Wl,-rpath,$ORIGIN")
else()
    set(CMAKE_CXX_FLAGS_DEBUG           "/MTd /Zi /Ob0 /Od /RTC1 /EHsc /D_DEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE         "/MT /Zi /Ox /Ob2 /EHsc")
    set(CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL "/OPT:REF /LTCG") 
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "/OPT:REF") 
    set(CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO "/OPT:REF /DEBUG:FULL") 
endif()

include_directories("common")
include_directories("controller")
include_directories("loader")
include_directories("invoker")
include_directories("extensions")
include_directories("../client/headers")
include_directories("intercept_dll")

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
