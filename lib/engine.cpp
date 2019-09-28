#include <iostream>
#include <string>
#include <memory>

#include "brickengine/engine.hpp"
#include "brickengine/rendering/renderer.hpp"
#include "brickengine/rendering/renderable_factory.hpp"

#include "SDL2/SDL2_gfxPrimitives.h"
#include "SDL2/SDL.h"

void destory_window(SDL_Window* w) {
    SDL_DestroyWindow(w);
}
void destory_renderer(SDL_Renderer* r) {
    SDL_DestroyRenderer(r);
}

BrickEngine::BrickEngine(const std::string window_name, const int window_width, const int window_heigth) : window(nullptr, nullptr) {
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::cout << "SDL failed to init! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    //std::unique_ptr<SDL_Window, SDL_Window_deleter> window_ptr(SDL_CreateWindow(
    //  window_name.c_str(),
    //  SDL_WINDOWPOS_UNDEFINED,
    //  SDL_WINDOWPOS_UNDEFINED,
    //  window_width,
    //  window_heigth,
    //  0
    //), destory_window);
    //this->window = std::optional<std::unique_ptr<SDL_Window, SDL_Window_deleter>>(std::move(window_ptr));
    //if(!this->window.has_value())
    //{
    //    std::cout << "SDL window failed to open! SDL_Error: " << SDL_GetError() << std::endl;
    //    exit(1);
    //}

    SDL_Window* window_ptr(SDL_CreateWindow(
      window_name.c_str(),
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      window_width,
      window_heigth,
      0
    ));

    this->window = std::unique_ptr<SDL_Window, void(*)(SDL_Window*)>(window_ptr, destory_window);

    if(!this->window)
    {
        std::cout << "SDL window failed to open! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> renderer_ptr(SDL_CreateRenderer(this->window.get(), -1, SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer);
    this->renderer = std::shared_ptr<Renderer>(new Renderer(std::move(renderer_ptr)));

    this->renderableFactory = std::make_unique<RenderableFactory>(*new RenderableFactory(renderer));

    std::cout << "Window openend finsihed" << std::endl << std::endl;
}

BrickEngine::~BrickEngine() {
    SDL_Quit();
    std::cout << this->renderer.use_count() << std::endl;
}

void BrickEngine::delay(const Uint32 ms) const {
    SDL_Delay(ms);
}

const Uint32 BrickEngine::getTicks() {
    return SDL_GetTicks();
}

RenderableFactory* const BrickEngine::getRenderableFactory() const {
    return this->renderableFactory.get();
}

Renderer* const BrickEngine::getRenderer() const {
    return this->renderer.get();
}