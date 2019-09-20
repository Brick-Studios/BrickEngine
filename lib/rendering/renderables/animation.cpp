#include <string>
#include <memory>
#include <iostream>
#include "SDL2/SDL.h"

#include "brickengine/rendering/renderables/animation.hpp"
#include "brickengine/rendering/renderables/renderable.hpp"
#include "brickengine/engine.hpp"

Animation::Animation(SDL_Texture* texture, const Uint32 start_tick, const int speed, const int frames) : Renderable(texture){
    this->start_tick = start_tick;
    this->speed = speed;
    this->frames = frames;
}

SDL_Texture* const Animation::getTexture() {
    Uint32 ticks = BrickEngine::getTicks();
    // vage voorbeeld code
    int frame = 0;
    int x = frame * this->w;
    int y = 0;
    int w = this->w;
    int h = this->h;

    return 0;
}