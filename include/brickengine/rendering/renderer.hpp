#ifndef FILE_RENDERER_HPP
#define FILE_RENDERER_HPP

#include <functional>
#include <queue>
#include <vector>
#include <unordered_map>
#include <memory>

#include "SDL2/SDL.h"
#include "brickengine/rendering/renderables/renderable.hpp"
#include "brickengine/rendering/renderables/texture.hpp"
#include "brickengine/rendering/renderables/line.hpp"
#include "brickengine/rendering/renderables/circle.hpp"

class Circle;
class Texture;
class Line;
class Renderable;

class Renderer {
public:
    Renderer(std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> r, std::vector<int> layers);
    void clearScreen();
    void drawScreen();
    void queueRenderable(Renderable* r);
    SDL_Texture* createTextureFromSurface(SDL_Surface* surface) const;
    void render();
    void render(Texture& t);
    void render(Circle& renderable);
    void render(Line& renderable);
private:
    std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> sdl_renderer;
    std::unique_ptr<std::unordered_map<int, std::vector<Renderable*>>> renderQueue;
    std::vector<int> layers;
};

#endif