cmake_minimum_required (VERSION 3.0)

set(INTERCEPT_EXAMPLE_NAME "example_dll")


intercept_set_linker_options()

set(INTERCEPT_NAME "example_dll")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}example_dll")

file(GLOB INTERCEPT_EXAMPLE_SOURCES *.h *.hpp *.c *.cpp)
file(GLOB INTERCEPT_CLIENT_SOURCES  ../intercept/*.h ../intercept/*.hpp ../intercept/*.c ../intercept/*.cpp)
file(GLOB INTERCEPT_CLIENT_MAIN_SOURCES  ../intercept/client/*.h ../intercept/client/*.hpp ../intercept/client/*.c ../intercept/client/*.cpp)
file(GLOB INTERCEPT_CLIENT_SHARED_SOURCES  ../intercept/shared/*.h ../intercept/shared/*.hpp ../intercept/shared/*.c ../intercept/shared/*.cpp)


SOURCE_GROUP("example_dll" FILES ${INTERCEPT_EXAMPLE_SOURCES})
SOURCE_GROUP("intercept_includes" FILES ${INTERCEPT_CLIENT_SOURCES})
SOURCE_GROUP("intercept_includes\\client" FILES ${INTERCEPT_CLIENT_MAIN_SOURCES})
SOURCE_GROUP("intercept_includes\\shared" FILES ${INTERCEPT_CLIENT_SHARED_SOURCES})




add_library( ${INTERCEPT_EXAMPLE_NAME} SHARED ${INTERCEPT_EXAMPLE_SOURCES} ${INTERCEPT_CLIENT_SOURCES} ${INTERCEPT_CLIENT_MAIN_SOURCES} ${INTERCEPT_CLIENT_SHARED_SOURCES})
include_directories(${CMAKE_CURRENT_SOURCE_DIR} "../intercept")

target_link_libraries(${INTERCEPT_EXAMPLE_NAME} ${LINK_LIBS})
set_target_properties(${INTERCEPT_EXAMPLE_NAME} PROPERTIES PREFIX "")
set_target_properties(${INTERCEPT_EXAMPLE_NAME} PROPERTIES FOLDER example_dll)

if(CMAKE_COMPILER_IS_GNUCXX)
	set_target_properties(${INTERCEPT_EXAMPLE_NAME} PROPERTIES LINK_SEARCH_START_STATIC 1)
	set_target_properties(${INTERCEPT_EXAMPLE_NAME} PROPERTIES LINK_SEARCH_END_STATIC 1)
endif()