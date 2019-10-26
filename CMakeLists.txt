cmake_minimum_required(VERSION 3.12)

project(BrickEngine)
include(CMakePrintHelpers)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Force colors when using ninja with clang
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-fcolor-diagnostics)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-fdiagnostics-color=always)
endif()

# Add custom cmake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

add_subdirectory(include/brickengine)
add_subdirectory(lib)

option(BrickEngine_Test "Build the tests" ON)
if(BrickEngine_Test)
    enable_testing()
    add_subdirectory(tests)
endif()
