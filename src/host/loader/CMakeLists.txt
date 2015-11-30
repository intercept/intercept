file(GLOB_RECURSE INTERCEPT_LOADER_SOURCES *.h *.hpp *.c *.cpp)
intercept_set_linker_options()
file(GLOB LOADER_SOURCES *.h *.hpp *.c *.cpp)

SOURCE_GROUP("main" FILES ${LOADER_SOURCES})

add_library(loader_static STATIC ${LOADER_SOURCES})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories("C:/Program Files (x86)/Microsoft Research/Detours Express 3.0/include/")

target_link_libraries(loader_static controller_static "C:/Program Files (x86)/Microsoft Research/Detours Express 3.0/lib.X86/detours.lib" ${LINK_LIBS})
set_target_properties(loader_static PROPERTIES PREFIX "")
set_target_properties(loader_static PROPERTIES COMPILE_DEFINITIONS _STATIC)
set_target_properties(loader_static PROPERTIES FOLDER intercept)

if(CMAKE_COMPILER_IS_GNUCXX)
	set_target_properties(loader_static PROPERTIES LINK_SEARCH_START_STATIC 1)
	set_target_properties(loader_static PROPERTIES LINK_SEARCH_END_STATIC 1)
    set_target_properties(loader_static PROPERTIES LINK_SEARCH_START_STATIC 1)
	set_target_properties(loader_static PROPERTIES LINK_SEARCH_END_STATIC 1)
endif()
