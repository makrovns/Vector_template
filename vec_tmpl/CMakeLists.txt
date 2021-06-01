set(SOURCE_lib
vector_library.cpp
Vector_library.hpp
)

add_library(${PROJ}_lib STATIC ${SOURCE_lib})

target_include_directories(${PROJ}_lib PUBLIC ${CMAKE_CURRENT_LIST_DIR})

source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${SOURCE_lib})

set_property(TARGET ${PROJ}_lib PROPERTY FOLDER "Vector_lib")

add_subdirectory(tests)