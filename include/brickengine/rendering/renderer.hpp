#ifndef FILE_RENDERER_HPP
#define FILE_RENDERER_HPP

#include <functional>
#include <queue>
#include <vector>
#include <unordered_map>
#include <memory>

#include "SDL2/SDL.h"
#include "brickengine/rendering/renderables/renderable.hpp"

class Renderer {
public:
    Renderer(std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> r, std::vector<int> layers);
    void clearScreen();
    void drawScreen();
    void queueRenderable(Renderable& r);
    SDL_Texture* createTextureFromSurface(SDL_Surface* surface) const;
    void render();
private:
    std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> sdl_renderer;
    std::unique_ptr<std::unordered_map<int, Renderable&>> renderQueue;
    void render(Renderable& renderable);
    std::vector<int> layers;
};

#endif