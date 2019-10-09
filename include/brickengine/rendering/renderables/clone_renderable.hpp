#ifndef FILE_CLONE_RENDERABLE_HPP
#define FILE_CLONE_RENDERABLE_HPP

#include "brickengine/rendering/renderables/renderable.hpp"

class CloneRenderable : public Renderable {
public:
    CloneRenderable(int layer);
    virtual std::unique_ptr<CloneRenderable> clone() = 0;
};

#endif // FILE_CLONE_RENDERABLE_HPP