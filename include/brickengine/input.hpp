#include <iostream>
#include <unordered_map>
#include <algorithm>

#include "SDL2/SDL.h"

template<typename T>
class BrickInput {

public:
    BrickInput() = default;
    static BrickInput<T>& getInstance() {
        static BrickInput<T> INSTANCE;
        return INSTANCE;
    }
    void setInputMapping(std::unordered_map<SDL_Keycode, T>& gameInput) {
        inputMapping = gameInput;
        for(auto it : inputMapping) {
            inputs[it.second] = false;
        }
    }
    // This function is intended for the UI so the game loop is not affected.
    void popInput(T const input) {
        if(inputs.count(input))
            inputs[input] = false;
    }
    bool checkInput(T const input) const {
        if(inputs.count(input))
            return inputs.at(input);
        return false;
    }
    bool remapInput(T const input) {
        //Search for the old value
        auto oldInput = std::find_if(inputMapping.begin(),inputMapping.end(),
                                                    [&input](const std::pair<SDL_Keycode, T>& value)
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
    }
    void processInput() {
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
    }
private:
    // List of mapped inputs
    std::unordered_map<T, bool> inputs;
    // SDL inputs mapped to game input
    std::unordered_map<SDL_Keycode, T> inputMapping;

};