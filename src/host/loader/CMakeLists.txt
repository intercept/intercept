option(DEBUG_LOADER "DEBUG_LOADER" OFF)

if (DEBUG_LOADER)
    add_compile_definitions(LOADER_DEBUG=1)
endif()

file(GLOB_RECURSE INTERCEPT_LOADER_SOURCES *.h *.hpp *.c *.cpp)
intercept_set_linker_options()
file(GLOB LOADER_SOURCES *.h *.hpp *.c *.cpp)

SOURCE_GROUP("main" FILES ${LOADER_SOURCES})

file(GLOB INTERCEPT_CLIENT_SHARED_SOURCES  ../../client/headers/shared/vector.hpp ../../client/headers/shared/types.hpp ../../client/headers/shared/containers.hpp ../../client/intercept/shared/types.cpp ../../client/intercept/shared/containers.cpp)

SOURCE_GROUP("intercept_includes\\shared" FILES ${INTERCEPT_CLIENT_SHARED_SOURCES})

add_library(loader_static STATIC ${LOADER_SOURCES} ${INTERCEPT_CLIENT_SHARED_SOURCES})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(loader_static PROPERTIES PREFIX "")
set_target_properties(loader_static PROPERTIES COMPILE_DEFINITIONS _STATIC)
set_target_properties(loader_static PROPERTIES FOLDER intercept)

if(CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(loader_static PRIVATE "-fPIC")
    set_target_properties(loader_static PROPERTIES LINK_SEARCH_START_STATIC 1)
    set_target_properties(loader_static PROPERTIES LINK_SEARCH_END_STATIC 1)
    set_target_properties(loader_static PROPERTIES LINK_SEARCH_START_STATIC 1)
    set_target_properties(loader_static PROPERTIES LINK_SEARCH_END_STATIC 1)
endif()
