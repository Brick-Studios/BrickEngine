#target_link_libraries(BrickEngine SDL2::Main SDL2::Net)

target_sources(BrickEngine
    PRIVATE
        engine.cpp
        rendering/image.cpp
)
