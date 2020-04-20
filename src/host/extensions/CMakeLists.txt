file(GLOB_RECURSE INTERCEPT_EXTENSIONS_SOURCES *.h *.hpp *.c *.cpp)
intercept_set_linker_options()
file(GLOB INTERCEPT_EXTENSIONS_SOURCES *.h *.hpp *.c *.cpp)

SOURCE_GROUP("main" FILES ${INTERCEPT_EXTENSIONS_SOURCES})

add_library(extensions_static STATIC ${INTERCEPT_EXTENSIONS_SOURCES})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(extensions_static controller_static loader_static invoker_static ${LINK_LIBS})
set_target_properties(extensions_static PROPERTIES PREFIX "")
set_target_properties(extensions_static PROPERTIES COMPILE_DEFINITIONS _STATIC)
set_target_properties(extensions_static PROPERTIES FOLDER intercept)

if(CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(extensions_static PRIVATE "-fPIC")
    set_target_properties(extensions_static PROPERTIES LINK_SEARCH_START_STATIC 1)
    set_target_properties(extensions_static PROPERTIES LINK_SEARCH_END_STATIC 1)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_link_libraries(extensions_static ${CMAKE_DL_LIBS})
endif()
