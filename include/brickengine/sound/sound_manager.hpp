#ifndef FILE_SOUND_MANAGER_HPP
#define FILE_SOUND_MANAGER_HPP

#include <string>

#include "SDL2/SDL_mixer.h"

class SoundManager {
public:
    SoundManager();
    ~SoundManager();

    void playMusic(std::string path);
    void pauseMusic(const bool pause) const;
    void stopMusic();
private:
    Mix_Music *current_music = nullptr;
};

#endif // FILE_SOUND_MANAGER_HPP