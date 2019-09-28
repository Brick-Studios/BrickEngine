#include <memory>
#include <iostream>
#include <string>
#include <unordered_map>

#include "SDL2/SDL.h"

#include "brickengine/rendering/renderer.hpp"
#include "brickengine/engine.hpp"

Renderer::Renderer(std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> r) : sdl_renderer(std::move(r)) {
    //auto x = new std::unordered_map<unsigned int, Renderable&>();
    //renderQueue = std::make_unique<unsigned int, Renderable&>(*x);
}

Renderer::~Renderer() {
    auto x = 1;
}

void Renderer::render(Renderable& r) {
    //this->renderQueue->insert(r.getLayer(), r);
    SDL_Rect* src = (struct SDL_Rect*)r.getSrcRect();
    SDL_Rect* dst = (struct SDL_Rect*)r.getDstRect();
    SDL_RenderCopy(this->sdl_renderer.get(), r.getTexture(), src, dst);
};

SDL_Texture* Renderer::CreateTextureFromSurface(SDL_Surface* surface) const {
    return SDL_CreateTextureFromSurface(this->sdl_renderer.get(), surface);
}

void Renderer::drawScreen() {
    SDL_RenderPresent(this->sdl_renderer.get());
};

void Renderer::clearScreen() {
    SDL_RenderClear(this->sdl_renderer.get());
};
