#ifndef FILE_RECTANGLE_COLLISION_COMPONENT_HPP
#define FILE_RECTANGLE_COLLISION_COMPONENT_HPP

#include "brickengine/components/component_impl.hpp"

class RectangleColliderComponent : public ComponentImpl<RectangleColliderComponent> {
public:
    RectangleColliderComponent(double xScale, double yScale, double zScale, bool isTrigger);
    static std::string getNameStatic();

    // Data
    double xScale;
    double yScale;
    double zScale;
    bool isTrigger; // If the component is able to be moved through and only be used as a "trigger"
};

#endif // FILE_RECTANGLE_COLLISION_COMPONENT_HPP