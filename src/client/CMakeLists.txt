cmake_minimum_required (VERSION 3.8)

set_property(GLOBAL PROPERTY USE_FOLDERS ON) 

if (NOT CMAKE_BUILD_TYPE AND CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "No build type selected, default to Debug")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

option(DEVEL "DEVEL" ON)
option(USE_STATIC_LINKING "USE_STATIC_LINKING" ON)


if((CMAKE_CXX_COMPILER_ID MATCHES "Clang") OR (CMAKE_CXX_COMPILER_ID MATCHES "GNU"))
    SET(CMAKE_CXX_FLAGS "-std=c++1z -O2 -s -fPIC -fpermissive")
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
    set(CMAKE_SHARED_LINKER_FLAGS "-static-libgcc -static-libstdc++")
else()
    set(CMAKE_CXX_FLAGS_DEBUG "/D _DEBUG /MTd /Zi /Ob0 /Od /RTC1 /EHsc")
    set(CMAKE_CXX_FLAGS_MINSIZEREL     "/MT /Ox /Ob1 /D /EHsc NDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE       "/MT /Ox /Ob2 /D /EHsc NDEBUG")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MT /Zi /Ox /Ob2 /D /EHsc NDEBUG")
endif()
include_directories("intercept")


if(DEVEL)
    add_definitions(-DDEVEL)
endif()

include_directories(${CMAKE_CURRENT_BINARY_DIR}/intercept)


set(GLOBAL_SOURCES ${GLOBAL_RC})


add_subdirectory(intercept)



message("Build Type: ${CMAKE_BUILD_TYPE}")