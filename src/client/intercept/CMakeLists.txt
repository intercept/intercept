cmake_minimum_required (VERSION 3.0)

set(INTERCEPT_EXAMPLE_NAME "intercept_client")


intercept_set_linker_options()
add_definitions(/DINTERCEPT_NO_THREAD_SAFETY)
set(INTERCEPT_NAME "intercept_client")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}intercept_clientas")

file(GLOB INTERCEPT_CLIENT_SOURCES ../headers/*.h ../headers/*.hpp *.c *.cpp)
file(GLOB INTERCEPT_CLIENT_MAIN_SOURCES  ../headers/client/*.h ../headers/client/*.hpp ./client/*.c ./client/*.cpp)
file(GLOB INTERCEPT_CLIENT_SHARED_SOURCES  ../headers/shared/*.h ../headers/shared/*.hpp ./shared/*.c ./shared/*.cpp)
file(GLOB INTERCEPT_CLIENT_SQF_SHARED_SOURCES  ../headers/client/sqf/*.h ../headers/client/sqf/*.hpp ./client/sqf/*.c ./client/sqf/*.cpp)


SOURCE_GROUP("intercept_client" FILES ${INTERCEPT_CLIENT_SOURCES})
SOURCE_GROUP("intercept_client\\client" FILES ${INTERCEPT_CLIENT_MAIN_SOURCES})
SOURCE_GROUP("intercept_client\\shared" FILES ${INTERCEPT_CLIENT_SHARED_SOURCES})
SOURCE_GROUP("intercept_client\\client\\sqf" FILES ${INTERCEPT_CLIENT_SQF_SHARED_SOURCES})





add_library( ${INTERCEPT_EXAMPLE_NAME} STATIC ${INTERCEPT_CLIENT_SOURCES} ${INTERCEPT_CLIENT_MAIN_SOURCES} ${INTERCEPT_CLIENT_SHARED_SOURCES} ${INTERCEPT_CLIENT_SQF_SHARED_SOURCES})
include_directories(${CMAKE_CURRENT_SOURCE_DIR} "../headers")
include_directories(${CMAKE_CURRENT_SOURCE_DIR} "../headers/shared")
include_directories(${CMAKE_CURRENT_SOURCE_DIR} "../headers/client")
include_directories(${CMAKE_CURRENT_SOURCE_DIR} "../headers/client/sqf")

target_link_libraries(${INTERCEPT_EXAMPLE_NAME} ${LINK_LIBS})
set_target_properties(${INTERCEPT_EXAMPLE_NAME} PROPERTIES PREFIX "")
set_target_properties(${INTERCEPT_EXAMPLE_NAME} PROPERTIES FOLDER intercept_client)

if(CMAKE_COMPILER_IS_GNUCXX)
	set_target_properties(${INTERCEPT_EXAMPLE_NAME} PROPERTIES LINK_SEARCH_START_STATIC 1)
	set_target_properties(${INTERCEPT_EXAMPLE_NAME} PROPERTIES LINK_SEARCH_END_STATIC 1)
endif()