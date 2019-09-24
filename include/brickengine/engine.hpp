#ifndef FILE_BRICKENGINE_HPP
#define FILE_BRICKENGINE_HPP

#include <optional>
#include <iostream>
#include <string>
#include <memory>
#include <string>

#include "SDL2/SDL.h"
#include "SDL2/SDL2_gfxPrimitives.h"

#include "brickengine/rendering/renderer.hpp"
#include "brickengine/rendering/renderables/animation.hpp"
#include "brickengine/rendering/renderable_factory.hpp"

class BrickEngine {
public:
    BrickEngine(const std::string window_name, const int window_width, const int window_heigth);
    ~BrickEngine();
    void delay(const Uint32 ms) const;
    const static Uint32 getTicks();
private:
    using SDL_Window_deleter = void(*)(SDL_Window*);
    std::optional<std::unique_ptr<SDL_Window, SDL_Window_deleter>> window;
    std::optional<std::shared_ptr<Renderer>> renderer;
    std::optional<std::unique_ptr<RenderableFactory>> renderableFactory;
};

#endif /* FILE_BRICKENGINE_HPP */
