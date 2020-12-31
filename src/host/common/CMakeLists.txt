file(GLOB_RECURSE COMMON_SOURCES *.h *.hpp *.c *.cpp)
intercept_set_linker_options()


file(GLOB COMMON_SOURCES *.h *.hpp *.c *.cpp)



SOURCE_GROUP("common" FILES ${COMMON_SOURCES})





add_library(common_static STATIC ${COMMON_SOURCES})

set_target_properties(common_static PROPERTIES FOLDER intercept)

target_link_libraries(common_static)

if(CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(common_static PRIVATE "-fPIC")
endif()
