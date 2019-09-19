#ifndef FILE_RENDERER_HPP
#define FILE_RENDERER_HPP

#include <functional>

#include "SDL2/SDL.h"
#include "brickengine/rendering/renderables/image.hpp"

class Renderer {
public:
    Renderer(std::unique_ptr<const SDL_Renderer> r);
    void ClearScreen();
    void DrawScreen();
    void Render(const Renderable renderable);
    void Render(const Image renderable);
    void Render();
private:
    const std::unique_ptr<const SDL_Renderer> sdl_renderer;
};

#endif