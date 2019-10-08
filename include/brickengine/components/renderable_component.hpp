#ifndef FILE_RENDERABLE_COMPONENT_HPP
#define FILE_RENDERABLE_COMPONENT_HPP

#include "brickengine/components/component_impl.hpp"

class RenderableComponent : public ComponentImpl<RenderableComponent> {
    static std::string getNameStatic() {
        return "RenderableComponent";
    }
};

#endif /* FILE_RENDERABLE_COMPONENT_HPP */
