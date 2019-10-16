file(GLOB_RECURSE SRC_FILES RELATIVE ${CMAKE_CURRENT_LIST_DIR} *.c[p]*)

## Compiler options
# Make the compiler complain, a lot
# Force colors when using ninja with clang
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-fcolor-diagnostics)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-fdiagnostics-color=always)
endif()
# Turn on the address sanitizer for safety checks
option(BRICKENGINE_SANITIZER "Turn on the address sanitizer" OFF)
if(BRICKENGINE_SANITIZER)
    add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address)
endif()
add_compile_options(-Wall -Wextra -pedantic -Werror)

find_package(SDL2 REQUIRED)
find_package(SDL2_net REQUIRED)
find_package(SDL2_gfx REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

add_library(BrickEngine STATIC
    ${SRC_FILES}
)
target_include_directories(BrickEngine PUBLIC ../include)
target_link_libraries(BrickEngine
    PRIVATE SDL2::Main
    PRIVATE SDL2::Net
    PRIVATE SDL2::GFX
    PRIVATE SDL2::TTF
    PRIVATE SDL2::Image
)
target_compile_features(BrickEngine PUBLIC cxx_std_17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Export source file list so that it can be used for test compilation
set(SRC_FILES ${SRC_FILES} PARENT_SCOPE)
