#include "brickengine/components/click_component.hpp"

ClickComponent::ClickComponent(std::function<void ()> fn, double xScale, double yScale)
    : fn(fn), xScale(xScale), yScale(yScale) {}

std::string ClickComponent::getNameStatic() {
    return "ClickComponent";
}