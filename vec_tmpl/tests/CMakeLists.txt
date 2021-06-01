set(SOURCE_executable
tests.cpp)

add_executable(${PROJ}_tests ${SOURCE_executable})

target_link_libraries(${PROJ}_tests PUBLIC ${PROJ}_lib)

target_link_libraries(${PROJ}_tests PUBLIC gtest_main)

set_property(TARGET ${PROJ}_tests PROPERTY FOLDER "Vector_tests")