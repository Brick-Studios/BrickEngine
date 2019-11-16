#ifndef FILE_RECTANGLE_COLLISION_COMPONENT_HPP
#define FILE_RECTANGLE_COLLISION_COMPONENT_HPP

#include "brickengine/components/component_impl.hpp"

class RectangleColliderComponent : public ComponentImpl<RectangleColliderComponent> {
public:
    RectangleColliderComponent(double x_scale, double y_scale, double z_scale, bool is_trigger);
    static std::string getNameStatic();

    // Data
    double x_scale;
    double y_scale;
    double z_scale;
    bool is_trigger; // If the component is able to be moved through and only be used as a "trigger"
};

#endif // FILE_RECTANGLE_COLLISION_COMPONENT_HPP