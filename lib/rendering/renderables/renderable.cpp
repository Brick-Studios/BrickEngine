#include "brickengine/rendering/renderables/renderable.hpp"
#include "brickengine/rendering/renderables/data/rect.hpp"
#include "SDL2/SDL.h"

Renderable::Renderable(int layer) :
    layer(layer) {}

int Renderable::getLayer() const {
    return this->layer;
}