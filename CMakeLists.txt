cmake_minimum_required(VERSION 3.7)

project(SDL2Test)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package(SDL2 REQUIRED)
find_package(SDL2_net REQUIRED)

add_executable(SDL2Test Main.cpp)
target_link_libraries(${PROJECT_NAME} SDL2::Main SDL2::Net)
