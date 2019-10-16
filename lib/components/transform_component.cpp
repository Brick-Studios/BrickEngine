#include "brickengine/components/transform_component.hpp"

TransformComponent::TransformComponent(double xPos, double yPos, double xScale, double yScale)
                    : xPos(xPos), yPos(yPos), xScale(xScale), yScale(yScale) {}

std::string TransformComponent::getNameStatic() {
    return "TransformComponent";
}