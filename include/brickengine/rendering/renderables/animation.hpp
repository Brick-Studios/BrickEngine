#ifndef FILE_ANIMATION_HPP
#define FILE_ANIMATION_HPP

#include <string>
#include "SDL2/SDL.h"

#include "brickengine/rendering/renderables/renderable.hpp"

class Animation : public Renderable {
public:
    Animation(SDL_Texture* texture, const Uint32 start_tick, const int speed, const int frames);
    SDL_Texture* const getTexture() override;
private:
    Uint32 start_tick; //The tick the animation started at
    int speed; //How many ticks the same frame will be shown
    int frames; //How many frames the animation contains
};

#endif