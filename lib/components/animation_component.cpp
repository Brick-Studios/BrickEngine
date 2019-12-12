#include "brickengine/components/animation_component.hpp"

AnimationComponent::AnimationComponent(double update_time, int sprite_size)
    : update_time(update_time), sprite_size(sprite_size) {}

std::string AnimationComponent::getNameStatic() {
    return "AnimationComponent";
} 