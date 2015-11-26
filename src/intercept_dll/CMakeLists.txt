cmake_minimum_required (VERSION 3.0)

set(INTERCEPT_EXTENSION_NAME "intercept")

file(GLOB_RECURSE INTERCEPT_SOURCES *.h *.hpp *.c *.cpp)
intercept_set_linker_options()

set(INTERCEPT_NAME "intercept")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}intercept")

file(GLOB INTERCEPT_SOURCES *.h *.hpp *.c *.cpp)

SOURCE_GROUP("main" FILES ${INTERCEPT_SOURCES})

add_library( ${INTERCEPT_EXTENSION_NAME} SHARED ${INTERCEPT_SOURCES})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${INTERCEPT_EXTENSION_NAME} common_static loader_static controller_static invoker_static ${LINK_LIBS})
set_target_properties(${INTERCEPT_EXTENSION_NAME} PROPERTIES PREFIX "")
set_target_properties(${INTERCEPT_EXTENSION_NAME} PROPERTIES FOLDER intercept)

if(CMAKE_COMPILER_IS_GNUCXX)
	set_target_properties(${INTERCEPT_EXTENSION_NAME} PROPERTIES LINK_SEARCH_START_STATIC 1)
	set_target_properties(${INTERCEPT_EXTENSION_NAME} PROPERTIES LINK_SEARCH_END_STATIC 1)
    set_target_properties(${INTERCEPT_EXTENSION_NAME}_static PROPERTIES LINK_SEARCH_START_STATIC 1)
	set_target_properties(${INTERCEPT_EXTENSION_NAME}_static PROPERTIES LINK_SEARCH_END_STATIC 1)
endif()