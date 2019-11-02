add_subdirectory("../extern/googletest" "extern/googletest")

file(GLOB_RECURSE TEST_FILES RELATIVE ${CMAKE_CURRENT_LIST_DIR} *.c[p]*)

add_executable(BrickEngine_Test ${TEST_FILES})
# Make the compiler complain, a lot
target_compile_options(BrickEngine_Test
    PRIVATE -Wall -Wextra -pedantic -Werror)
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(BrickEngine_Test
        PRIVATE -fprofile-instr-generate -fcoverage-mapping)
    target_link_options(BrickEngine_Test
        PRIVATE -fprofile-instr-generate -fcoverage-mapping)
endif()
# Turn on the address sanitizer for safety checks
option(BRICKENGINE_TEST_SANITIZER "Turn on the address sanitizer" OFF)
if(BRICKENGINE_TEST_SANITIZER)
    target_compile_options(BrickEngine_Test
        PRIVATE -fsanitize=address -fno-omit-frame-pointer)
    target_link_options(BrickEngine_Test
        PRIVATE -fsanitize=address)
endif()
target_link_libraries(BrickEngine_Test PRIVATE
    BrickEngine
    gtest
    gmock
    gtest_main)
target_include_directories(BrickEngine_Test PRIVATE ${BRICKENGINE_INCLUDE_DIRECTORY})
add_test(NAME BrickEngine_Test COMMAND BrickEngine_Test)
set_target_properties(BrickEngine_Test PROPERTIES FOLDER tests)
