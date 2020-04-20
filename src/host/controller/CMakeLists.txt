file(GLOB_RECURSE INTERCEPT_CONTROLLER_SOURCES *.h *.hpp *.c *.cpp)
intercept_set_linker_options()
file(GLOB CONTROLLER_SOURCES *.h *.hpp *.c *.cpp)


SOURCE_GROUP("main" FILES ${CONTROLLER_SOURCES})

add_library(controller_static STATIC ${CONTROLLER_SOURCES})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})


target_link_libraries(controller_static common_static ${LINK_LIBS})
set_target_properties(controller_static PROPERTIES PREFIX "")
set_target_properties(controller_static PROPERTIES COMPILE_DEFINITIONS _STATIC)
set_target_properties(controller_static PROPERTIES FOLDER intercept)

if(CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(controller_static PRIVATE "-fPIC")
    set_target_properties(controller_static PROPERTIES LINK_SEARCH_START_STATIC 1)
    set_target_properties(controller_static PROPERTIES LINK_SEARCH_END_STATIC 1)
    set_target_properties(controller_static PROPERTIES LINK_SEARCH_START_STATIC 1)
    set_target_properties(controller_static PROPERTIES LINK_SEARCH_END_STATIC 1)
endif()
