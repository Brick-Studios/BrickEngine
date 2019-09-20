#ifndef FILE_RENDERABLE_HPP
#define FILE_RENDERABLE_HPP

#include <memory>
#include "SDL2/SDL.h"

class Renderable {
public:
    int x;
    int y;
    int w;
    int h;
    int layer;
    Renderable(SDL_Texture* texture);
    virtual SDL_Texture* const getTexture();
protected:
    SDL_Texture* texture;
};

#endif /* FILE_RENDERABLE_HPP */