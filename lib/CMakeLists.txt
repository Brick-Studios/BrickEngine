#target_link_libraries(BrickEngine SDL2::Main SDL2::Net)

target_link_libraries(BrickEngine
    PRIVATE SDL2::Main
    PRIVATE SDL2::Net)

target_sources(BrickEngine
    PUBLIC
        BrickEngine.cpp
)
