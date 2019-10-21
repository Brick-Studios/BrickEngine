cmake_minimum_required(VERSION 3.12)

project(BrickEngine)
include(CMakePrintHelpers)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

add_subdirectory(include/brickengine)
add_subdirectory(lib)

option(BrickEngine_Test "Build the tests" ON)
if(BrickEngine_Test)
    enable_testing()
    add_subdirectory(tests)
endif()
