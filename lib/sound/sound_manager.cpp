#include "brickengine/sound/sound_manager.hpp"

#include <iostream>
#include <string>

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

SoundManager::SoundManager() {
    if (SDL_Init( SDL_INIT_AUDIO ) != 0) {
        std::cout << "SDL failed to init! SDL_Error: " << SDL_GetError() << std::endl;
    }

    //Initialize SDL2_mixer
    int flags = MIX_INIT_MP3;
    if(Mix_Init(flags) != flags) {
        std::cout << "Mixer failed to init! Mix_Error: " << Mix_GetError() << std::endl; 
    }
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
}

void SoundManager::playMusic(std::string path) {
    stopMusic();
    
    const std::string full_path = "assets/sound/" + path;
    current_music = Mix_LoadMUS(full_path.c_str());
    Mix_PlayMusic(current_music, -1); // The -1 is for infinite repeat
}

void SoundManager::pauseMusic(const bool pause) const {
    if(current_music != nullptr) {
        if(pause) {
            Mix_PauseMusic();
        } else {
            Mix_ResumeMusic();
        }
    }
}

void SoundManager::stopMusic() {
    if(current_music != nullptr) {
        // Unload current music
        Mix_FreeMusic(current_music);
        current_music = nullptr;
    }
}

SoundManager::~SoundManager() {
    Mix_CloseAudio();
}