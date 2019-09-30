#include <memory>
#include <string>
#include <iostream>

#include "brickengine/rendering/renderable_factory.hpp"
#include "brickengine/rendering/renderer.hpp"
#include "brickengine/rendering/renderables/renderable.hpp"
#include "brickengine/engine.hpp"
#include "brickengine/rendering/renderables/rect.hpp"

RenderableFactory::RenderableFactory(std::shared_ptr<Renderer> r) : renderer(r) {
}

std::unique_ptr<Renderable> RenderableFactory::createImage(std::string path, int layer, std::unique_ptr<Rect> dst) const {
    SDL_Texture* texture = this->createBMPTexture(path);

    return std::unique_ptr<Renderable>(new Renderable(texture, layer, std::move(dst)));
}

SDL_Texture* RenderableFactory::createBMPTexture(std::string path) const {
    SDL_Surface* surface = SDL_LoadBMP(path.c_str());

    if (surface == nullptr) {
        std::cout << "Failed to load surface " << path
            << " error : " << SDL_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* t = renderer.get()->CreateTextureFromSurface(surface);
    SDL_FreeSurface(surface);
    return t;
}