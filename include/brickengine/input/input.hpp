#include <iostream>
#include <unordered_map>

#include "brickengine/input/player_input.hpp"
#include "SDL2/SDL.h"

class BrickInput {

public:
    BrickInput() = default;
    static BrickInput& getInstance();
    void setInputMapping(std::unordered_map<SDL_Keycode, PlayerInput>& gameInput);
    // This function is intended for the UI so the game loop is not affected.
    void popInput(PlayerInput const input);
    bool checkInput(PlayerInput const input);
    bool remapInput(PlayerInput const input);
    void processInput();
private:
    // List of mapped inputs
    std::unordered_map<PlayerInput, bool> inputs;
    // SDL inputs mapped to game input
    std::unordered_map<SDL_Keycode, PlayerInput> inputMapping;

};