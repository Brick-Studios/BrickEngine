#include "brickengine/components/colliders/rectangle_collider_component.hpp"

RectangleColliderComponent::RectangleColliderComponent(double xScale, double yScale, double zScale, bool isTrigger)
    : xScale(xScale), yScale(yScale), zScale(zScale), isTrigger(isTrigger) {}

std::string RectangleColliderComponent::getNameStatic() {
    return "RectangleColliderComponent";
}
