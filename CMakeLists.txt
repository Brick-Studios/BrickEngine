cmake_minimum_required(VERSION 3.15)

project(BrickEngine)

option(CMAKE_EXPORT_COMPILE_COMMANDS "Generate compile_commands.json in build directory" ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)
find_package(SDL2 REQUIRED)
find_package(SDL2_net REQUIRED)

add_library(BrickEngine STATIC
    ""
)
target_compile_features(BrickEngine PUBLIC cxx_std_17)

add_subdirectory(lib)

target_include_directories(BrickEngine
    PUBLIC include
    PRIVATE lib
)

