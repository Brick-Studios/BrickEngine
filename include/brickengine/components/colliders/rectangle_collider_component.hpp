#ifndef FILE_SQUARE_COLLISION_COMPONENT_HPP
#define FILE_SQUARE_COLLISION_COMPONENT_HPP

#include "brickengine/components/component_impl.hpp"

class RectangleColliderComponent : public ComponentImpl<RectangleColliderComponent> {
public:
    RectangleColliderComponent(double xScale, double yScale, double zScale);
    static std::string getNameStatic();

    // data
    double xScale;
    double yScale;
    double zScale;
};

#endif //FILE_SQUARE_COLLISION_COMPONENT_HPP