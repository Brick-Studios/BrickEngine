#include "brickengine/input/input.hpp"
#include "SDL2/SDL.h"

BrickInput::BrickInput() {

}

void BrickInput::processInput(){
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0 )
    {
        if(e.type == SDL_KEYDOWN)
        {
            std::cout << "Key pressed!!!" << std::endl;
        }
    }
}

void BrickInput::setInputMapping(std::unordered_map<std::string, std::string>& gameInput) {
    inputMapping = gameInput;
}