#include "brickengine/components/transform_component.hpp"

TransformComponent::TransformComponent(double x_pos, double y_pos, double x_scale, double y_scale, Direction x_direction, Direction y_direction)
                    : x_pos(x_pos), y_pos(y_pos), x_scale(x_scale), y_scale(y_scale), x_direction(x_direction), y_direction(y_direction) {}

std::string TransformComponent::getNameStatic() {
    return "TransformComponent";
}