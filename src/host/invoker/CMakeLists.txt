file(GLOB_RECURSE INTERCEPT_INVOKER_SOURCES *.h *.hpp *.c *.cpp)
intercept_set_linker_options()
file(GLOB INVOKER_SOURCES *.h *.hpp *.c *.cpp)

SOURCE_GROUP("main" FILES ${INVOKER_SOURCES})



add_library(invoker_static STATIC ${INVOKER_SOURCES})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})



target_link_libraries(invoker_static controller_static loader_static ${LINK_LIBS})
set_target_properties(invoker_static PROPERTIES PREFIX "")
set_target_properties(invoker_static PROPERTIES COMPILE_DEFINITIONS _STATIC)
set_target_properties(invoker_static PROPERTIES FOLDER intercept)

if(CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(invoker_static PRIVATE "-fPIC")
    set_target_properties(invoker_static PROPERTIES LINK_SEARCH_START_STATIC 1)
    set_target_properties(invoker_static PROPERTIES LINK_SEARCH_END_STATIC 1)
    set_target_properties(invoker_static PROPERTIES LINK_SEARCH_START_STATIC 1)
    set_target_properties(invoker_static PROPERTIES LINK_SEARCH_END_STATIC 1)
endif()
