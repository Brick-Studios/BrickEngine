cmake_minimum_required(VERSION 3.13.5)

project(BrickEngine)
include(CMakePrintHelpers)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Force colors when using ninja with clang
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-fcolor-diagnostics)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-fdiagnostics-color=always)
endif()

# Add custom cmake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

if(APPLE) 
	set(CMAKE_CXX_FLAGS "-I/usr/local/include/ -D_THREAD_SAFE")
endif()

add_subdirectory(include/brickengine)
add_subdirectory(lib)

option(BRICKENGINE_TEST "Build the tests" ON)
if(BRICKENGINE_TEST)
    enable_testing()
    add_subdirectory(tests)
endif()
