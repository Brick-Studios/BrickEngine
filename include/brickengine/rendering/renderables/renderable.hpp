#ifndef FILE_RENDERABLE_HPP
#define FILE_RENDERABLE_HPP

#include <memory>
#include "SDL2/SDL.h"

class Renderer;

class Renderable {
public:
    Renderable(int layer);
    virtual ~Renderable() = default;
    virtual void render(Renderer& r) = 0;
    int getLayer() const;
protected:
    int layer;
};

#endif /* FILE_RENDERABLE_HPP */