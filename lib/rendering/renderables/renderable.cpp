#include "brickengine/rendering/renderables/renderable.hpp"
#include "SDL2/SDL.h"

Renderable::Renderable(SDL_Texture* texture){
    this->texture = texture;
}

SDL_Texture* const Renderable::getTexture() {
    return this->texture;
}