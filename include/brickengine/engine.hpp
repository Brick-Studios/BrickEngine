#ifndef FILE_BRICKENGINE_HPP
#define FILE_BRICKENGINE_HPP

#include <optional>
#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_net.h"

struct SDL_Window;

class BrickEngine {
public:
    void OpenWindow() {
        SDL_Init(SDL_INIT_VIDEO);

        window = SDL_CreateWindow(
          "SDL2Test",
          SDL_WINDOWPOS_UNDEFINED,
          SDL_WINDOWPOS_UNDEFINED,
          640,
          480,
          0
        );

        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        SDL_Delay(300000);
        std::cout << "Window openend finsihed";
    }

    void CloseWindow() {
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

private:
    SDL_Window* window;
};

#endif /* FILE_BRICKENGINE_HPP */
