#include <memory>
#include "SDL2/SDL.h"
#include "brickengine/rendering/renderables/texture.hpp"
#include "brickengine/rendering/renderer.hpp"

Texture::Texture(SDL_Texture* texture, int layer, std::unique_ptr<Rect> dst) :
    Renderable(layer), texture(std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)>(texture, SDL_DestroyTexture)),
    dst(std::move(dst)) {}

Texture::Texture(SDL_Texture* texture, int layer, std::unique_ptr<Rect> dst, std::unique_ptr<Rect> src) :
    Renderable(layer), texture(std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)>(texture, SDL_DestroyTexture)),
    src(std::move(src)), dst(std::move(dst)) {}

void Texture::render(Renderer& r) {
    r.render(*this);
}



Rect* Texture::getSrcRect() const {
    return this->src.get();
}

Rect* Texture::getDstRect() const {
    return this->dst.get();
}

SDL_Texture* Texture::getTexture() const {
    return this->texture.get();
}