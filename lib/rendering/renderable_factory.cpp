#include <memory>
#include <string>
#include <iostream>

#include "brickengine/rendering/renderable_factory.hpp"
#include "brickengine/rendering/renderer.hpp"
#include "brickengine/rendering/renderables/renderable.hpp"
#include "brickengine/engine.hpp"

RenderableFactory::RenderableFactory(std::shared_ptr<Renderer> r){
    this->renderer = r;
}

std::unique_ptr<Renderable> RenderableFactory::createImage(std::string path) const {
    SDL_Texture* texture = this->createBMPTexture(path);

    std::unique_ptr<Renderable> r = std::make_unique<Renderable>(Renderable(texture));

    return r;
}

std::unique_ptr<Renderable> RenderableFactory::createAnimation(std::string path, int speed, int frames) const {
    SDL_Texture* texture = this->createBMPTexture(path);

    const Uint32 start_tick = BrickEngine::getTicks();
    std::unique_ptr<Animation> r = std::make_unique<Animation>(*new Animation(texture, start_tick, speed, frames));

    return r;
}

SDL_Texture* RenderableFactory::createBMPTexture(std::string path) const {
    SDL_Surface* surface = SDL_LoadBMP(path.c_str());

    if (surface == nullptr) {
        std::cout << "Failed to load surface " << path
            << " error : " << SDL_GetError() << std::endl;
        return nullptr;
    }

    return renderer->CreateTextureFromSurface(surface);
}