#ifndef FILE_RENDERER_HPP
#define FILE_RENDERER_HPP

#include <functional>

#include "SDL2/SDL.h"
#include "brickengine/rendering/renderables/renderable.hpp"

class Renderer {
public:
    Renderer(SDL_Renderer* r);
    ~Renderer();
    void clearScreen();
    void drawScreen();
    void render(const Renderable renderable);
    void render();
private:
    SDL_Renderer* sdl_renderer;
};

#endif