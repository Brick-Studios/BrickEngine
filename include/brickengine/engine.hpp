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
#include "brickengine/rendering/renderable_factory.hpp"

class BrickEngine {
public:
    BrickEngine(const std::string window_name, const int window_width, const int window_heigth, std::vector<int> layers);
    ~BrickEngine();
    void delay(const Uint32 ms) const;
    static Uint32 getTicks();
    RenderableFactory* getRenderableFactory() const;
    Renderer* getRenderer() const;
private:
    std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> window;
    std::shared_ptr<Renderer> renderer;
    std::unique_ptr<RenderableFactory> renderableFactory;
};

#endif /* FILE_BRICKENGINE_HPP */
