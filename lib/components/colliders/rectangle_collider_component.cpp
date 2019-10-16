#include "brickengine/components/colliders/rectangle_collider_component.hpp"

RectangleColliderComponent::RectangleColliderComponent(double xScale, double yScale, double zScale)
    : xScale(xScale), yScale(yScale), zScale(zScale) {}

std::string RectangleColliderComponent::getNameStatic() {
    return "RectangleColliderComponent";
}
