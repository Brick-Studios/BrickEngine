#ifndef FILE_RENDERABLE_HPP
#define FILE_RENDERABLE_HPP

#include <memory>
#include "SDL2/SDL.h"

class Renderable {
public:
    Renderable(SDL_Texture* texture);
    virtual SDL_Texture* const getTexture();
    virtual SDL_Rect* getSrcRect();
    virtual SDL_Rect* getDstRect();
    int getLayer() const;
protected:
    SDL_Texture* texture;
    SDL_Rect src;
    SDL_Rect dst;
    int layer;
};

#endif /* FILE_RENDERABLE_HPP */