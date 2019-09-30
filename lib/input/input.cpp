#include "brickengine/input/input.hpp"
#include "brickengine/input/player_input.hpp"
#include "SDL2/SDL.h"
#include <algorithm>

BrickInput& BrickInput::getInstance() {
    static BrickInput INSTANCE;
    return INSTANCE;
};

void BrickInput::processInput(){
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        // Checking if input is mapped.
        if(inputMapping.find(e.key.keysym.sym) != inputMapping.end() && e.key.repeat == 0) {
            switch(e.type) {
                case SDL_KEYDOWN:
                    inputs[inputMapping[e.key.keysym.sym]] = true;
                    break;
                case SDL_KEYUP:
                    inputs[inputMapping[e.key.keysym.sym]] = false;
                default:
                    break;
            }
            
        }
    }
};

void BrickInput::setInputMapping(std::unordered_map<SDL_Keycode, PlayerInput>& gameInput) {
    inputMapping = gameInput;
    for(auto it : inputMapping) {
        inputs[it.second] = false;
    }
};

bool BrickInput::remapInput(PlayerInput input) {
    //Search for the old value
    auto oldInput = std::find_if(inputMapping.begin(),inputMapping.end(),
                                                [&input](const std::pair<SDL_Keycode, PlayerInput>& value)
                                               { return value.second == input; });
    SDL_Event e;
    while(true) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_KEYDOWN) {
                //Current key matches old key
                if(e.key.keysym.sym == oldInput->first) {
                    return true;
                }
                //Input is not already used
                if(inputMapping.count(e.key.keysym.sym) == 0)
                {
                    inputMapping[e.key.keysym.sym] = input;
                    //Removing old key mapping
                    inputMapping.erase(oldInput->first);
                    return true; 
                }
                //Key is used
                if(inputMapping.count(e.key.keysym.sym) == 1)
                    return false;
            }
        }
    }
};

bool BrickInput::checkInput(PlayerInput const input) {
    if(inputs.count(input))
        return inputs[input];
    return false;
};

void BrickInput::popInput(PlayerInput const input) {
    if(inputs.count(input))
        inputs[input] = false;
}
