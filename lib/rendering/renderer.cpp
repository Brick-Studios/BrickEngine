#include <memory>
#include <iostream>
#include <string>
#include <unordered_map>

#include "SDL2/SDL.h"

#include "brickengine/rendering/renderer.hpp"
#include "brickengine/engine.hpp"

Renderer::Renderer(SDL_Renderer* r) {
    sdl_renderer = r;
    auto x = new std::unordered_map<unsigned int, Renderable&>();
    renderQueue = std::make_unique<unsigned int, Renderable&>(*x);
}

Renderer::~Renderer(){
    SDL_DestroyRenderer(sdl_renderer);
}

void Renderer::render(Renderable& r) {
    //this->renderQueue->insert(r.getLayer(), r);
};

SDL_Texture* Renderer::CreateTextureFromSurface(SDL_Surface* surface) const {
    return SDL_CreateTextureFromSurface(this->sdl_renderer, surface);
}

void Renderer::drawScreen() {
    SDL_RenderPresent(this->sdl_renderer);
};

void Renderer::clearScreen() {
    SDL_RenderClear(this->sdl_renderer);
};
