#include <iostream>
#include <string>
#include <memory>

#include "brickengine/engine.hpp"
#include "brickengine/rendering/renderer.hpp"

#include "SDL2/SDL2_gfxPrimitives.h"
#include "SDL2/SDL.h"

void BrickEngine::Start(const std::string window_name) {
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::cout << "SDL failed to init! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    window = std::optional{ std::make_unique(SDL_CreateWindow(
      window_name.c_str(),
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      640,
      480,
      0
    ))};
    
    if(!window.has_value())
    {
        std::cout << "SDL window failed to open! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    //Update the surface
    SDL_UpdateWindowSurface(window.value);

    SDL_LoadBMP( "02_getting_an_image_on_the_screen/hello_world.bmp" );

    // Test for drawing a circle and a line
    //circleRGBA(renderer, 150, 150, 50, 50, 50, 50, 50);

    std::unique_ptr<SDL_Renderer> sdl_renderer = std::make_unique<SDL_Renderer>(SDL_CreateRenderer(window.value, -1, SDL_RENDERER_ACCELERATED));
    renderer = std::make_unique<Renderer>(new Renderer(sdl_renderer));
 //    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
//    SDL_RenderClear(renderer);
//    SDL_RenderPresent(renderer);

    std::cout << "Window openend finsihed";
}

void BrickEngine::Shutdown() {
    SDL_DestroyWindow(window.value);
    SDL_Quit();
}

const void BrickEngine::Delay(const Uint32 ms) {
    SDL_Delay(ms);
}
