#include "brickengine/components/transform_component.hpp"

TransformComponent::TransformComponent(double xPos, double yPos, double xScale, double yScale)
                    : xPos(xPos), yPos(yPos), xScale(xScale), yScale(yScale) {}

std::string TransformComponent::getNameStatic() {
    return "TransformComponent";
}

// Getters and Setters
void TransformComponent::setXPos(double x){
    this->xPos = x;
}
double TransformComponent::getXPos() const {
    return xPos;
}
void TransformComponent::setYPos(double y) {
    this->yPos = y;
}
double TransformComponent::getYPos() const {
    return yPos;
}
void TransformComponent::setXScale(double s) {
    this->xScale = s;
}
double TransformComponent::getXScale() const {
    return xScale;
}
void TransformComponent::setYScale(double s) {
    this->yScale = s;
}
double TransformComponent::getYScale() const {
    return yScale;
}