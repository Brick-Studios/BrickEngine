cmake_minimum_required(VERSION 3.15)

project(BrickEngine)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)
find_package(SDL2 REQUIRED)
find_package(SDL2_net REQUIRED)

add_library(BrickEngine STATIC
    ""
)

add_subdirectory(lib)

#target_include_directories(BrickEngine
#    PUBLIC include
#    PRIVATE src
#)


