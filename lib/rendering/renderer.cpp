#include <memory>
#include <iostream>
#include <string>
#include "SDL2/SDL.h"
#include "brickengine/rendering/renderer.hpp"
#include "brickengine/engine.hpp"

Renderer::Renderer(SDL_Renderer* r) {
    sdl_renderer = r;
}

Renderer::~Renderer(){
    SDL_DestroyRenderer(sdl_renderer);
}

SDL_Texture* Renderer::CreateTextureFromSurface(SDL_Surface* surface) const {
    return SDL_CreateTextureFromSurface(this->sdl_renderer, surface);
}