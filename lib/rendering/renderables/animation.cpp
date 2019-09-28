#include <string>
#include <memory>
#include <iostream>
#include "SDL2/SDL.h"

#include "brickengine/rendering/renderables/animation.hpp"
#include "brickengine/rendering/renderables/renderable.hpp"
#include "brickengine/engine.hpp"

//TODO een animation heeft een bewegingsrichting (x, y) en dat is de hoeveelheid beweging die de animatie per frame uitvoerd

//Animation::Animation(SDL_Texture* texture, Uint32 start_tick, const int speed, const int frames) : Renderable(texture){
//    this->start_tick = start_tick;
//    this->speed = speed;
//    this->frames = frames;
//}

//SDL_Rect* Animation::getSrcRect() {
//    //Calculate frame
//    Uint32 ticks = BrickEngine::getTicks();
//
//    Uint32 diff = ticks - this->start_tick;
//    int frames = diff / this->frames;
//    int frame = frames / this->speed;
//
//    // vage voorbeeld code
//    //this->src.x = frame * this->w;
//    //this->src.y = 0;
//    //this->src.w = this->w;
//    //this->src.h = this->h;
//
//    return nullptr;
//}