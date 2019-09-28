#include "brickengine/rendering/renderables/renderable.hpp"
#include "brickengine/rendering/renderables/rect.hpp"
#include "SDL2/SDL.h"

Renderable::Renderable(SDL_Texture* texture, std::unique_ptr<Rect> dst) :
    texture(texture), dst(std::move(dst)) {
}
Renderable::Renderable(SDL_Texture* texture, std::unique_ptr<Rect> dst, std::unique_ptr<Rect> src) :
    texture(texture), dst(std::move(dst)), src(std::move(src)) {
}

SDL_Texture* const Renderable::getTexture() {
    return this->texture;
}

Rect* Renderable::getSrcRect() {
    return this->src.get();
}

Rect* Renderable::getDstRect() {
    return this->dst.get();
}

int Renderable::getLayer() const {
    return this->layer;
}