#include <iostream>
#include <string>
#include <memory>

#include "brickengine/engine.hpp"
#include "brickengine/rendering/renderer.hpp"

#include "SDL2/SDL2_gfxPrimitives.h"
#include "SDL2/SDL.h"

BrickEngine::BrickEngine(const std::string window_name, const int window_width, const int window_heigth) {
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::cout << "SDL failed to init! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    window = SDL_CreateWindow(
      window_name.c_str(),
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      window_width,
      window_heigth,
      0
    );
    
    if(!window.has_value())
    {
        std::cout << "SDL window failed to open! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    auto sdl_renderer = SDL_CreateRenderer(window.value(), -1, SDL_RENDERER_ACCELERATED);
    renderer = std::make_shared<Renderer>(*new Renderer(sdl_renderer));

    renderableFactory = std::make_unique<RenderableFactory>(*new RenderableFactory(renderer.value()));

    std::cout << "Window openend finsihed";
}

BrickEngine::~BrickEngine() {
    SDL_DestroyWindow(window.value());
    SDL_Quit();
}

const void BrickEngine::delay(const Uint32 ms) {
    SDL_Delay(ms);
}

const Uint32 BrickEngine::getTicks() {
    return SDL_GetTicks();
}