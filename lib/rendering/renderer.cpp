#include <memory>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "SDL2/SDL.h"
#include "SDL2/SDL2_gfxPrimitives.h"

#include "brickengine/rendering/renderer.hpp"
#include "brickengine/rendering/renderables/line.hpp"
#include "brickengine/engine.hpp"

Renderer::Renderer(std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> r, std::vector<int> layers) : sdl_renderer(std::move(r)) {
    std::sort(layers.begin(), layers.end());
    this->layers = layers;
    renderQueue = std::make_unique<std::unordered_map<int, std::vector<Renderable*>>>();
    for (int layer : layers) {
        renderQueue.get()->insert({layer, std::vector<Renderable*>()});
    }

    // SDL renderer startup
    SDL_Color color = { 0, 0, 0, 0 };
    SDL_BlendMode mode = SDL_BlendMode::SDL_BLENDMODE_BLEND;

    SDL_SetRenderDrawColor(this->sdl_renderer.get(), color.r, color.g, color.b, color.a);
    SDL_SetRenderDrawBlendMode(this->sdl_renderer.get(), mode);
}

void Renderer::queueRenderable(Renderable* r) {
    if (renderQueue.get()->count(r->getLayer()) < 1) {
        std::cout << "had to create a new vec layer for some reason, debug this!" << std::endl;
        this->renderQueue.get()->insert({ r->getLayer(), std::vector<Renderable*>() });
    }

    this->renderQueue.get()->at(r->getLayer()).push_back(r);
}

void Renderer::render(Texture& r) {
    SDL_Rect* src = (struct SDL_Rect*)r.getSrcRect();
    SDL_Rect* dst = (struct SDL_Rect*)r.getDstRect();
    SDL_RenderCopyEx(this->sdl_renderer.get(), r.getTexture(), src, dst, 0, nullptr, r.getFlip());
}
void Renderer::render(Circle& r) {
    if (r.getFilled())
        filledCircleRGBA(this->sdl_renderer.get(), r.getX(), r.getY(), r.getRadius(), r.getColor().r, r.getColor().g, r.getColor().b, r.getColor().a);
    else
        circleRGBA(this->sdl_renderer.get(), r.getX(), r.getY(), r.getRadius(), r.getColor().r, r.getColor().g, r.getColor().b, r.getColor().a);
}
void Renderer::render(Line& r) {
    lineRGBA(this->sdl_renderer.get(), r.getX1(), r.getY1(), r.getX2(), r.getY2(), r.getColor().r, r.getColor().g, r.getColor().b, r.getColor().a);
}

SDL_Texture* Renderer::createTextureFromSurface(SDL_Surface* surface) const {
    return SDL_CreateTextureFromSurface(this->sdl_renderer.get(), surface);
}

void Renderer::drawScreen() {
    for(size_t i = 0; i < layers.size(); i++) {
        for (auto r : this->renderQueue.get()->at(layers[i])) {
            SDL_Color prev;
            SDL_BlendMode mode;

            SDL_GetRenderDrawBlendMode(this->sdl_renderer.get(), &mode);
            SDL_GetRenderDrawColor(this->sdl_renderer.get(), &prev.r, &prev.g, &prev.b, &prev.a);
            r->render(*this);
            SDL_SetRenderDrawColor(this->sdl_renderer.get(), prev.r, prev.g, prev.b, prev.a);
            SDL_SetRenderDrawBlendMode(this->sdl_renderer.get(), mode);
        }
    }

    SDL_RenderPresent(this->sdl_renderer.get());
}

void Renderer::clearScreen() {
    SDL_RenderClear(this->sdl_renderer.get());
    for (int layer : layers) {
        renderQueue.get()->at(layer).clear();
    }
}
