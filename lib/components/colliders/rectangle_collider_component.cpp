#include "brickengine/components/colliders/rectangle_collider_component.hpp"

RectangleColliderComponent::RectangleColliderComponent(double xScale, double yScale, double zScale, bool isTrigger,
                                                       bool should_displace)
    : x_scale(xScale), y_scale(yScale), z_scale(zScale), is_trigger(isTrigger), should_displace(should_displace) {}

std::string RectangleColliderComponent::getNameStatic() {
    return "RectangleColliderComponent";
}
