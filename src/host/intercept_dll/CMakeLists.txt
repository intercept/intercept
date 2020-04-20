cmake_minimum_required (VERSION 3.8)

if(USE_64BIT_BUILD)
    set(INTERCEPT_EXTENSION_NAME "intercept_x64")
else()
    set(INTERCEPT_EXTENSION_NAME "intercept")
endif()

file(GLOB_RECURSE INTERCEPT_SOURCES *.h *.hpp *.c *.cpp)
intercept_set_linker_options()

set(INTERCEPT_NAME "intercept")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}intercept")

file(GLOB INTERCEPT_SOURCES *.h *.hpp *.c *.cpp)

SOURCE_GROUP("main" FILES ${INTERCEPT_SOURCES})

add_library( ${INTERCEPT_EXTENSION_NAME} SHARED ${INTERCEPT_SOURCES})
add_library( ${INTERCEPT_EXTENSION_NAME}_static ${INTERCEPT_SOURCES})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${INTERCEPT_EXTENSION_NAME} common_static loader_static controller_static invoker_static extensions_static ${LINK_LIBS})
set_target_properties(${INTERCEPT_EXTENSION_NAME} PROPERTIES PREFIX "")
set_target_properties(${INTERCEPT_EXTENSION_NAME} PROPERTIES FOLDER intercept)

if((CMAKE_CXX_COMPILER_ID MATCHES "Clang") OR (CMAKE_CXX_COMPILER_ID MATCHES "GNU"))
	target_compile_options(
		${INTERCEPT_EXTENSION_NAME} PRIVATE 
		"-std=c++1z"
		"$<$<CONFIG:Release>:-O3>"
		"-s" #remove -s to enable debug symbols. Also maybe add -g or -g3
		"-fPIC"
		"-fpermissive"
		"-pthread"
		"-static-libgcc"
		"-static-libstdc++"
		"-Wno-ignored-attributes"
		"-static"
		"$<$<CONFIG:Release>:-ffunction-sections>"
		"$<$<CONFIG:Release>:-fdata-sections>"
	)
	target_link_options(${INTERCEPT_EXTENSION_NAME} PRIVATE "-fPIC"
	"$<$<CONFIG:Release>:-Wl,--gc-sections>"
	"$<$<OR:$<CONFIG:Release>>:-Wl,--strip-all>"
    "-Wl,-rpath,$ORIGIN"
	) 
	set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")

	target_link_libraries(${INTERCEPT_EXTENSION_NAME} "libstdc++.a")
	find_package (Threads)
	target_link_libraries (${INTERCEPT_EXTENSION_NAME} ${CMAKE_THREAD_LIBS_INIT})
else()
	target_compile_options(
		${INTERCEPT_EXTENSION_NAME} PRIVATE 
		"/MP" "/Zi" "/EHsc"
		"$<$<CONFIG:Release>:/MT>"
		"$<$<CONFIG:Debug>:/MTd>"
		"$<$<CONFIG:Release>:/Ox>"
		"$<$<CONFIG:Release>:/Ob2>"
		"$<$<CONFIG:Debug>:/Ob0>"
		"$<$<CONFIG:Release>:/Oi>"
		"$<$<CONFIG:Debug>:/Od>"
		"$<$<CONFIG:Debug>:/RTC1>"
		"$<$<CONFIG:Release>:/Ot>"
		"$<$<CONFIG:Release>:/DNDEBUG>"
		"$<$<CONFIG:Debug>:/D_DEBUG>"
	)
	target_link_options(${INTERCEPT_EXTENSION_NAME} PRIVATE "/OPT:REF" "/OPT:ICF" "/DEBUG:FULL") 
endif()


if(INTERCEPT_BUILD2RV)
    set_target_properties(${INTERCEPT_EXTENSION_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/rv")
    set_target_properties(${INTERCEPT_EXTENSION_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/rv")
    set_target_properties(${INTERCEPT_EXTENSION_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/rv")
    set_target_properties(${INTERCEPT_EXTENSION_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${PROJECT_SOURCE_DIR}/rv")
    set_target_properties(${INTERCEPT_EXTENSION_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${PROJECT_SOURCE_DIR}/rv")
endif()


if(CMAKE_COMPILER_IS_GNUCXX)
    set_target_properties(${INTERCEPT_EXTENSION_NAME} PROPERTIES LINK_SEARCH_START_STATIC 1)
    set_target_properties(${INTERCEPT_EXTENSION_NAME} PROPERTIES LINK_SEARCH_END_STATIC 1)
    set_target_properties(${INTERCEPT_EXTENSION_NAME}_static PROPERTIES LINK_SEARCH_START_STATIC 1)
    set_target_properties(${INTERCEPT_EXTENSION_NAME}_static PROPERTIES LINK_SEARCH_END_STATIC 1)
endif()
