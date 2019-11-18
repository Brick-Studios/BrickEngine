#include "brickengine/components/colliders/rectangle_collider_component.hpp"

RectangleColliderComponent::RectangleColliderComponent(double xScale, double yScale, double zScale, bool isTrigger)
    : x_scale(xScale), y_scale(yScale), z_scale(zScale), is_trigger(isTrigger) {}

std::string RectangleColliderComponent::getNameStatic() {
    return "RectangleColliderComponent";
}
