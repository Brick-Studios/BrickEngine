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

    void setInputMapping(std::unordered_map<int, std::unordered_map<SDL_Keycode, T>>& gameInput) {
        inputMapping = gameInput;
        for(auto [playerId, mapping] : inputMapping) {
            for(auto [sdl_key, input] : mapping){
                inputs[playerId][input] = false;
            }
        }
    }
    
    // This function is intended for the UI so the game loop is not affected.
    void popInput(int playerId, T const input) {
        if(inputs[playerId].count(input))
            inputs[playerId][input] = false;
    }

    bool checkInput(int playerId, T const input) {
        if(inputs[playerId].count(input))
            return inputs[playerId].at(input);
        return false;
    }

    bool remapInput(int playerId, T const input) {
        //Search for the old value
        auto oldInput = std::find_if(inputMapping.at(playerId).begin(),inputMapping.at(playerId).end(),
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
                    if(inputMapping.at(playerId).count(e.key.keysym.sym) == 0)
                    {
                        inputMapping[playerId][e.key.keysym.sym] = input;
                        //Removing old key mapping
                        inputMapping.at(playerId).erase(oldInput->first);
                        return true; 
                    }
                    //Key is used
                    if(inputMapping.at(playerId).count(e.key.keysym.sym) == 1)
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
            for(auto [playerId, mapping] : inputs){
                if(inputMapping.at(playerId).find(e.key.keysym.sym) != inputMapping.at(playerId).end() && e.key.repeat == 0) {
                    switch(e.type) {
                        case SDL_KEYDOWN:
                            inputs[playerId][inputMapping[playerId][e.key.keysym.sym]] = true;
                            break;
                        case SDL_KEYUP:
                            inputs[playerId][inputMapping[playerId][e.key.keysym.sym]] = false;
                        default:
                            break;
                    }
                    
                }
            }
        }
    }
private:
    // List of mapped inputs
    std::unordered_map<int, std::unordered_map<T, bool>> inputs;
    // SDL inputs mapped to game input
    std::unordered_map<int, std::unordered_map<SDL_Keycode, T>> inputMapping;
};