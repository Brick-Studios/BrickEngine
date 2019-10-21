add_subdirectory("../extern/googletest" "extern/googletest")

file(GLOB_RECURSE TEST_FILES RELATIVE ${CMAKE_CURRENT_LIST_DIR} *.c[p]*)

add_executable(BrickEngine_Test ${TEST_FILES})
target_link_libraries(BrickEngine_Test PRIVATE
    BrickEngine
    gtest
    gmock
    gtest_main)
target_include_directories(BrickEngine_Test PRIVATE ${BRICKENGINE_INCLUDE_DIRECTORY})
add_test(NAME BrickEngine_Test COMMAND BrickEngine_Test)
set_target_properties(BrickEngine_Test PROPERTIES FOLDER tests)
