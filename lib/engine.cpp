#include <iostream>
#include <string>

#include "brickengine/engine.hpp"

#include "SDL2/SDL2_gfxPrimitives.h"
#include "SDL2/SDL.h"

BrickEngine::BrickEngine() {
    window = nullptr;
    renderer = nullptr;
    screenSurface = nullptr;
}
BrickEngine::~BrickEngine() {

}

void BrickEngine::Start(const std::string window_name) {
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
      640,
      480,
      0
    );
    if(window == nullptr)
    {
        std::cout << "SDL window failed to open! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    //Get window surface
    screenSurface = SDL_GetWindowSurface( window );

    //Fill the surface white
    SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
    
    //Update the surface
    SDL_UpdateWindowSurface( window );

    SDL_LoadBMP( "02_getting_an_image_on_the_screen/hello_world.bmp" );

    // Test for drawing a circle and a line
    //circleRGBA(renderer, 150, 150, 50, 50, 50, 50, 50);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE); 
 //    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
//    SDL_RenderClear(renderer);
//    SDL_RenderPresent(renderer);

    std::cout << "Window openend finsihed";
}

void BrickEngine::Shutdown() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void BrickEngine::Delay(Uint32 ms) {
    SDL_Delay(ms);
}
