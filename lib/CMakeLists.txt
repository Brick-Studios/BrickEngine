file(GLOB_RECURSE BRICKENGINE_SRC_FILES RELATIVE ${CMAKE_CURRENT_LIST_DIR} *.c[p]*)

find_package(SDL2 REQUIRED)
find_package(SDL2_net REQUIRED)
find_package(SDL2_gfx REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

add_library(BrickEngine STATIC
    ${BRICKENGINE_SRC_FILES}
)
# Make the compiler complain, a lot
target_compile_options(BrickEngine
    PRIVATE -Wall -Wextra -pedantic -Werror)
if (BRICKENGINE_TEST)
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        target_compile_options(BrickEngine
            PRIVATE -fprofile-instr-generate -fcoverage-mapping)
        target_link_options(BrickEngine
            PRIVATE -fprofile-instr-generate -fcoverage-mapping)
    endif()
endif()
target_include_directories(BrickEngine PUBLIC ../include)
target_link_libraries(BrickEngine
    PRIVATE SDL2::Main
    PRIVATE SDL2::Net
    PRIVATE SDL2::GFX
    PRIVATE SDL2::TTF
    PRIVATE SDL2::Image
    PRIVATE SDL2::Mixer
)
target_compile_features(BrickEngine PUBLIC cxx_std_17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Export source file list so that it can be used for test compilation
set(BRICKENGINE_SRC_FILES ${BRICKENGINE_SRC_FILES} PARENT_SCOPE)
