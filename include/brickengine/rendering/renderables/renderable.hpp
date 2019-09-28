#ifndef FILE_RENDERABLE_HPP
#define FILE_RENDERABLE_HPP

#include <memory>
#include "SDL2/SDL.h"
#include "brickengine/rendering/renderables/rect.hpp"

class Renderable {
public:
    Renderable(SDL_Texture* texture, std::unique_ptr<Rect> src);
    Renderable(SDL_Texture* texture, std::unique_ptr<Rect> src, std::unique_ptr<Rect> dst);
    virtual SDL_Texture* const getTexture();
    virtual Rect* getSrcRect();
    virtual Rect* getDstRect();
    int getLayer() const;
protected:
    SDL_Texture* texture;
    std::unique_ptr<Rect> src;
    std::unique_ptr<Rect> dst;
    int layer;
};

#endif /* FILE_RENDERABLE_HPP */