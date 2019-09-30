#include <iostream>
#include <string>
#include <memory>

#include "brickengine/engine.hpp"
#include "brickengine/rendering/renderer.hpp"
#include "brickengine/rendering/renderable_factory.hpp"

#include "SDL2/SDL2_gfxPrimitives.h"
#include "SDL2/SDL.h"

BrickEngine::BrickEngine(const std::string window_name, const int window_width, const int window_heigth, std::vector<int> layers) : window(nullptr, nullptr) {
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) != 0 )
    {
        std::cout << "SDL failed to init! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    SDL_Window* window_ptr(SDL_CreateWindow(
      window_name.c_str(),
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      window_width,
      window_heigth,
      0
    ));
    if(!window_ptr)
    {
        std::cout << "SDL window failed to open! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
    this->window = std::unique_ptr<SDL_Window, void(*)(SDL_Window*)>(window_ptr, SDL_DestroyWindow);



    SDL_Renderer* renderer_ptr(SDL_CreateRenderer(this->window.get(), -1, SDL_RENDERER_ACCELERATED));
    if(!renderer_ptr)
    {
        std::cout << "SDL renderer failed to open! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
    std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> renderer_unique_ptr(renderer_ptr, SDL_DestroyRenderer);
    this->renderer = std::shared_ptr<Renderer>(new Renderer(std::move(renderer_unique_ptr), layers));

    this->renderableFactory = std::unique_ptr<RenderableFactory>(new RenderableFactory(renderer));

    std::cout << "Window openend finished" << std::endl;
}

BrickEngine::~BrickEngine() {
    SDL_Quit();
}

void BrickEngine::delay(const Uint32 ms) const {
    SDL_Delay(ms);
}

Uint32 BrickEngine::getTicks() {
    return SDL_GetTicks();
}

RenderableFactory* BrickEngine::getRenderableFactory() const {
    return this->renderableFactory.get();
}

Renderer* BrickEngine::getRenderer() const {
    return this->renderer.get();
}