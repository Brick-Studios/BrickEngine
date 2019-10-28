#include "brickengine/components/click_component.hpp"

ClickComponent::ClickComponent(std::function<void ()> fn) : fn(fn) {}

std::string ClickComponent::getNameStatic() {
    return "ClickComponent";
}