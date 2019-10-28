#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <tuple>
#include <utility>

#include "SDL2/SDL.h"
#include "brickengine/input_keycode.hpp"

template<typename T>
class BrickInput {
public:
    BrickInput(){
        generateInputs();
    }

    static BrickInput<T>& getInstance() {
        static BrickInput<T> INSTANCE;
        return INSTANCE;
    }

    void setInputMapping(std::unordered_map<int, std::unordered_map<InputKeyCode, T>>& gameInput) {
        inputMapping = gameInput;
        for(auto [playerId, mapping] : inputMapping) {
            for(auto [sdl_key, input] : mapping){
                std::ignore = sdl_key;
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
                                                    [&input](const std::pair<InputKeyCode, T>& value)
                                                   { return value.second == input; });
        SDL_Event e;
        while(true) {
            while(SDL_PollEvent(&e)) {
                if(e.type == SDL_KEYDOWN) {
                    auto inputkeycode = convertSDLKeycodeInputKeyCode(e.key.keysym.sym);
                    if(inputkeycode.has_value()) {
                        //Current key matches old key
                        if(inputkeycode.value() == oldInput->first) {
                            return true;
                        }
                        //Input is not already used
                        if(inputMapping.at(playerId).count(inputkeycode.value()) == 0)
                        {
                            inputMapping[playerId][inputkeycode.value()] = input;
                            //Removing old key mapping
                            inputMapping.at(playerId).erase(oldInput->first);
                            return true; 
                        }
                        //Key is used
                        if(inputMapping.at(playerId).count(inputkeycode.value()) == 1)
                            return false;
                    }
                }
            }
        }
    }

    void processInput() {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            switch (e.type) {
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                    // Checking if input is mapped.
                    for(auto [playerId, mapping] : inputs){
                        std::ignore = mapping;
                        auto input = convertSDLKeycodeInputKeyCode(e.key.keysym.sym);
                        if(input.has_value()) {
                            if(inputMapping.at(playerId).find(input.value()) != inputMapping.at(playerId).end() && e.key.repeat == 0) {
                                switch(e.type) {
                                    case SDL_KEYDOWN:
                                        inputs[playerId][inputMapping[playerId][input.value()]] = true;
                                        break;
                                    case SDL_KEYUP:
                                        inputs[playerId][inputMapping[playerId][input.value()]] = false;
                                    default:
                                        break;
                                }
                            }
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                    // Checking if input is mapped.
                    for(auto [playerId, mapping] : inputs){
                        std::ignore = mapping;
                        auto input = convertSDLKeycodeInputKeyCode(e.button.button);
                        if(input.has_value()) {
                            if(inputMapping.at(playerId).find(input.value()) != inputMapping.at(playerId).end()) {
                                switch(e.button.state) {
                                    case SDL_PRESSED:
                                        inputs[playerId][inputMapping[playerId][input.value()]] = true;
                                        break;
                                    case SDL_RELEASED:
                                        inputs[playerId][inputMapping[playerId][input.value()]] = false;
                                    default:
                                        break;
                                }
                            }
                        }
                    }
                    break;
            }
        }
    }

    std::pair<int, int> getMousePosition() {
        int x, y;
        SDL_GetMouseState(&x, &y);
        return { x, y };
    }
private:
    // List of mapped inputs
    std::unordered_map<int, std::unordered_map<T, bool>> inputs;
    // SDL inputs mapped to game input
    std::unordered_map<int, std::unordered_map<InputKeyCode, T>> inputMapping;
    std::unordered_map<InputKeyCode, SDL_Keycode> sdl_mapping;
    std::unordered_map<SDL_Keycode, InputKeyCode> keycode_mapping;

    std::optional<SDL_Keycode> convertInputKeyCodeToSDLKeycode(InputKeyCode i) {
        auto input = sdl_mapping.find(i);
        if(input != sdl_mapping.end())
            return std::optional<SDL_Keycode>(input->second);
        return std::nullopt;
    }
    std::optional<InputKeyCode> convertSDLKeycodeInputKeyCode(SDL_Keycode s) {
        auto input = keycode_mapping.find(s);
        if(input != keycode_mapping.end())
            return std::optional<InputKeyCode>(input->second);
        return std::nullopt;
    }

    void generateInputs() {
        // Mapping for the SDL_mapping unordered_map
        // Numbers
        sdl_mapping.insert({InputKeyCode::EKey_0, SDLK_0});
        sdl_mapping.insert({InputKeyCode::EKey_1, SDLK_1});
        sdl_mapping.insert({InputKeyCode::EKey_2, SDLK_2});
        sdl_mapping.insert({InputKeyCode::EKey_3, SDLK_3});
        sdl_mapping.insert({InputKeyCode::EKey_4, SDLK_4});
        sdl_mapping.insert({InputKeyCode::EKey_5, SDLK_5});
        sdl_mapping.insert({InputKeyCode::EKey_6, SDLK_6});
        sdl_mapping.insert({InputKeyCode::EKey_7, SDLK_7});
        sdl_mapping.insert({InputKeyCode::EKey_8, SDLK_8});
        sdl_mapping.insert({InputKeyCode::EKey_9, SDLK_9});

        // Letters
        sdl_mapping.insert({InputKeyCode::EKey_a, SDLK_a});
        sdl_mapping.insert({InputKeyCode::EKey_b, SDLK_b});
        sdl_mapping.insert({InputKeyCode::EKey_c, SDLK_c});
        sdl_mapping.insert({InputKeyCode::EKey_d, SDLK_d});
        sdl_mapping.insert({InputKeyCode::EKey_e, SDLK_e});
        sdl_mapping.insert({InputKeyCode::EKey_f, SDLK_f});
        sdl_mapping.insert({InputKeyCode::EKey_g, SDLK_g});
        sdl_mapping.insert({InputKeyCode::EKey_h, SDLK_h});
        sdl_mapping.insert({InputKeyCode::EKey_i, SDLK_i});
        sdl_mapping.insert({InputKeyCode::EKey_j, SDLK_j});
        sdl_mapping.insert({InputKeyCode::EKey_k, SDLK_k});
        sdl_mapping.insert({InputKeyCode::EKey_l, SDLK_l});
        sdl_mapping.insert({InputKeyCode::EKey_m, SDLK_m});
        sdl_mapping.insert({InputKeyCode::EKey_n, SDLK_n});
        sdl_mapping.insert({InputKeyCode::EKey_o, SDLK_o});
        sdl_mapping.insert({InputKeyCode::EKey_p, SDLK_p});
        sdl_mapping.insert({InputKeyCode::EKey_q, SDLK_q});
        sdl_mapping.insert({InputKeyCode::EKey_r, SDLK_r});
        sdl_mapping.insert({InputKeyCode::EKey_s, SDLK_s});
        sdl_mapping.insert({InputKeyCode::EKey_t, SDLK_t});
        sdl_mapping.insert({InputKeyCode::EKey_u, SDLK_u});
        sdl_mapping.insert({InputKeyCode::EKey_v, SDLK_v});
        sdl_mapping.insert({InputKeyCode::EKey_w, SDLK_w});
        sdl_mapping.insert({InputKeyCode::EKey_x, SDLK_x});
        sdl_mapping.insert({InputKeyCode::EKey_y, SDLK_y});
        sdl_mapping.insert({InputKeyCode::EKey_z, SDLK_z});

        // Arrow keys
        sdl_mapping.insert({InputKeyCode::EKey_right, SDLK_RIGHT});
        sdl_mapping.insert({InputKeyCode::EKey_left, SDLK_LEFT});
        sdl_mapping.insert({InputKeyCode::EKey_up, SDLK_UP});
        sdl_mapping.insert({InputKeyCode::EKey_down, SDLK_DOWN});

        // Special
        sdl_mapping.insert({InputKeyCode::EKey_lshift, SDLK_LSHIFT});
        sdl_mapping.insert({InputKeyCode::EKey_lctrl, SDLK_LCTRL});
        sdl_mapping.insert({InputKeyCode::EKey_space, SDLK_SPACE});
        sdl_mapping.insert({InputKeyCode::Ekey_enter, SDLK_KP_ENTER});
        sdl_mapping.insert({InputKeyCode::EKey_backspace, SDLK_BACKSPACE});

        // Mouse input
        sdl_mapping.insert({InputKeyCode::EKey_mouse_left, SDL_BUTTON_LEFT});
        sdl_mapping.insert({InputKeyCode::EKey_mouse_right, SDL_BUTTON_RIGHT});

        // Mapping for the unordered_map keycode_mapping
        // Numbers
        keycode_mapping.insert({SDLK_0, InputKeyCode::EKey_0});
        keycode_mapping.insert({SDLK_1, InputKeyCode::EKey_1});
        keycode_mapping.insert({SDLK_2, InputKeyCode::EKey_2});
        keycode_mapping.insert({SDLK_3, InputKeyCode::EKey_3});
        keycode_mapping.insert({SDLK_4, InputKeyCode::EKey_4});
        keycode_mapping.insert({SDLK_5, InputKeyCode::EKey_5});
        keycode_mapping.insert({SDLK_6, InputKeyCode::EKey_6});
        keycode_mapping.insert({SDLK_7, InputKeyCode::EKey_7});
        keycode_mapping.insert({SDLK_8, InputKeyCode::EKey_8});
        keycode_mapping.insert({SDLK_9, InputKeyCode::EKey_9});

        // Letters
        keycode_mapping.insert({SDLK_a, InputKeyCode::EKey_a});
        keycode_mapping.insert({SDLK_b, InputKeyCode::EKey_b});
        keycode_mapping.insert({SDLK_c, InputKeyCode::EKey_c});
        keycode_mapping.insert({SDLK_d, InputKeyCode::EKey_d});
        keycode_mapping.insert({SDLK_e, InputKeyCode::EKey_e});
        keycode_mapping.insert({SDLK_f, InputKeyCode::EKey_f});
        keycode_mapping.insert({SDLK_g, InputKeyCode::EKey_g});
        keycode_mapping.insert({SDLK_h, InputKeyCode::EKey_h});
        keycode_mapping.insert({SDLK_i, InputKeyCode::EKey_i});
        keycode_mapping.insert({SDLK_j, InputKeyCode::EKey_j});
        keycode_mapping.insert({SDLK_k, InputKeyCode::EKey_k});
        keycode_mapping.insert({SDLK_l, InputKeyCode::EKey_l});
        keycode_mapping.insert({SDLK_m, InputKeyCode::EKey_m});
        keycode_mapping.insert({SDLK_n, InputKeyCode::EKey_n});
        keycode_mapping.insert({SDLK_o, InputKeyCode::EKey_o});
        keycode_mapping.insert({SDLK_p, InputKeyCode::EKey_p});
        keycode_mapping.insert({SDLK_q, InputKeyCode::EKey_q});
        keycode_mapping.insert({SDLK_r, InputKeyCode::EKey_r});
        keycode_mapping.insert({SDLK_s, InputKeyCode::EKey_s});
        keycode_mapping.insert({SDLK_t, InputKeyCode::EKey_t});
        keycode_mapping.insert({SDLK_u, InputKeyCode::EKey_u});
        keycode_mapping.insert({SDLK_v, InputKeyCode::EKey_v});
        keycode_mapping.insert({SDLK_w, InputKeyCode::EKey_w});
        keycode_mapping.insert({SDLK_x, InputKeyCode::EKey_x});
        keycode_mapping.insert({SDLK_y, InputKeyCode::EKey_y});
        keycode_mapping.insert({SDLK_z, InputKeyCode::EKey_z});

        // Arrow keys
        keycode_mapping.insert({SDLK_RIGHT, InputKeyCode::EKey_right});
        keycode_mapping.insert({SDLK_LEFT, InputKeyCode::EKey_left});
        keycode_mapping.insert({SDLK_UP, InputKeyCode::EKey_up});
        keycode_mapping.insert({SDLK_DOWN, InputKeyCode::EKey_down});

        // Special
        keycode_mapping.insert({SDLK_LSHIFT, InputKeyCode::EKey_lshift});
        keycode_mapping.insert({SDLK_LCTRL, InputKeyCode::EKey_lctrl});
        keycode_mapping.insert({SDLK_SPACE, InputKeyCode::EKey_space});
        keycode_mapping.insert({SDLK_KP_ENTER, InputKeyCode::Ekey_enter});
        keycode_mapping.insert({SDLK_BACKSPACE, InputKeyCode::EKey_backspace});

        // Mouse input
        keycode_mapping.insert({SDL_BUTTON_LEFT, InputKeyCode::EKey_mouse_left});
        keycode_mapping.insert({SDL_BUTTON_RIGHT, InputKeyCode::EKey_mouse_right});
    }
};