#ifndef FILE_RENDERER_HPP
#define FILE_RENDERER_HPP

#include <functional>
#include <queue>
#include <vector>
#include <unordered_map>

#include "SDL2/SDL.h"
#include "brickengine/rendering/renderables/renderable.hpp"

class Renderer {
public:
    Renderer(SDL_Renderer* r);
    ~Renderer();
    void clearScreen();
    void drawScreen();
    void render(Renderable& renderable);
    SDL_Texture* CreateTextureFromSurface(SDL_Surface* surface) const;
    void render();
private:
    SDL_Renderer* sdl_renderer;
    std::unique_ptr<std::unordered_map<unsigned int, Renderable&>> renderQueue;
};

#endif