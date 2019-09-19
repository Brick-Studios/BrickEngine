#ifndef FILE_BRICKENGINE_HPP
#define FILE_BRICKENGINE_HPP

#include <optional>
#include <iostream>
#include <string>
#include <memory>

#include "SDL2/SDL.h"
#include "SDL2/SDL2_gfxPrimitives.h"

class BrickEngine {
public:
    BrickEngine();
    void Start(const std::string window_name);
    void Shutdown();
    const void Delay(const Uint32 ms);
    const Uint32 GetTicks();
private:
    std::optional<std::unique_ptr<SDL_Window>> window;
    std::optional<std::unique_ptr<Renderer>> renderer;
};

#endif /* FILE_BRICKENGINE_HPP */
