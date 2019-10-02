#include <memory>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "SDL2/SDL.h"

#include "brickengine/rendering/renderer.hpp"
#include "brickengine/engine.hpp"

Renderer::Renderer(std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> r, std::vector<int> layers) : sdl_renderer(std::move(r)) {
    std::sort(layers.begin(), layers.end());
    this->layers = layers;
    renderQueue = std::unique_ptr<std::unordered_map<int, Renderable&>>(new std::unordered_map<int, Renderable&>());
}

void Renderer::queueRenderable(Renderable& r) {
    this->renderQueue.get()->insert({ r.getLayer(), r });
}

void Renderer::render(Renderable& r) {
    SDL_Rect* src = (struct SDL_Rect*)r.getSrcRect();
    SDL_Rect* dst = (struct SDL_Rect*)r.getDstRect();
    SDL_RenderCopy(this->sdl_renderer.get(), r.getTexture(), src, dst);
}

SDL_Texture* Renderer::createTextureFromSurface(SDL_Surface* surface) const {
    return SDL_CreateTextureFromSurface(this->sdl_renderer.get(), surface);
}

void Renderer::drawScreen() {
    auto renderQueue = this->renderQueue.get();

    for(unsigned int i = 0; i < layers.size(); i++) {
        auto bucket = renderQueue->bucket(layers[i]);
        for (auto o = renderQueue->begin(bucket); o != renderQueue->end(bucket); o++) {
            this->render(o->second);
        }
    }

    SDL_RenderPresent(this->sdl_renderer.get());
}

void Renderer::clearScreen() {
    SDL_RenderClear(this->sdl_renderer.get());
    renderQueue->clear();
}
