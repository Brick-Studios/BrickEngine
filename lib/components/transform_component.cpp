#include "brickengine/components/transform_component.hpp"

TransformComponent::TransformComponent(double xPos, double yPos, double xScale, double yScale, Direction xDirection, Direction yDirection)
                    : xPos(xPos), yPos(yPos), xScale(xScale), yScale(yScale), xDirection(xDirection), yDirection(yDirection) {}

std::string TransformComponent::getNameStatic() {
    return "TransformComponent";
}