#include "brickengine/input/input.hpp"
#include "brickengine/input/player_input.hpp"
#include "SDL2/SDL.h"

BrickInput& BrickInput::getInstance() {
    static BrickInput INSTANCE;
    return INSTANCE;
};

void BrickInput::processInput(){
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        // Checking if input is mapped.
        if(inputMapping.find(e.key.keysym.sym) != inputMapping.end()) {
            if (e.type == SDL_KEYDOWN)
                inputs[inputMapping[e.key.keysym.sym]] = true;
            else
                inputs[inputMapping[e.key.keysym.sym]] = false;
        }
    }
};

void BrickInput::setInputMapping(std::unordered_map<SDL_Keycode, PlayerInput>& gameInput) {
    inputMapping = gameInput;
    for(auto it : inputMapping) {
        inputs[it.second] = false;
    }
};