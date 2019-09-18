cmake_minimum_required(VERSION 3.12)
project(BrickEngine)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_net REQUIRED)
find_package(SDL2_gfx REQUIRED)

add_library(BrickEngine STATIC
    ""
)
target_link_libraries(BrickEngine
    PRIVATE SDL2::Main
    PRIVATE SDL2::Net)

target_compile_features(BrickEngine PUBLIC cxx_std_17)

add_subdirectory(lib)
add_subdirectory(include/brickengine)

target_include_directories(BrickEngine
    PUBLIC include
    PRIVATE lib
)

