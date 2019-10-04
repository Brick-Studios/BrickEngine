#include <memory>
#include "SDL2/SDL.h"
#include "brickengine/rendering/renderables/texture.hpp"
#include "brickengine/rendering/renderer.hpp"

void destroyT(SDL_Texture* t) {
    SDL_DestroyTexture(t);
}

Texture::Texture(SDL_Texture* texture, int layer, std::unique_ptr<Rect> dst) :
    texture(std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)>(texture, destroyT)),
    dst(std::move(dst)), Renderable(layer) {}

Texture::Texture(SDL_Texture* texture, int layer, std::unique_ptr<Rect> dst, std::unique_ptr<Rect> src) :
    texture(std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)>(texture, destroyT)),
    dst(std::move(dst)), src(std::move(src)), Renderable(layer) {}

void Texture::render(Renderer& r) {
    r.render(*this);
}



Rect* Texture::getSrcRect() {
    return this->src.get();
}

Rect* Texture::getDstRect() {
    return this->dst.get();
}

SDL_Texture* Texture::getTexture() {
    return this->texture.get();
}