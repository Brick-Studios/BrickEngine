file(GLOB_RECURSE SRC_FILES RELATIVE ${CMAKE_CURRENT_LIST_DIR} *.c[p]*)

target_sources(BrickEngine
    PRIVATE
        engine.cpp
        entities/entity_manager.cpp
        rendering/image.cpp
find_package(SDL2 REQUIRED)
find_package(SDL2_net REQUIRED)
find_package(SDL2_gfx REQUIRED)

add_library(BrickEngine STATIC
    ${SRC_FILES}
)
target_include_directories(BrickEngine PUBLIC ../include)
target_link_libraries(BrickEngine
    PRIVATE SDL2::Main
    PRIVATE SDL2::Net
)
target_compile_features(BrickEngine PUBLIC cxx_std_17)

# Export source file list so that it can be used for test compilation
set(SRC_FILES ${SRC_FILES} PARENT_SCOPE)
