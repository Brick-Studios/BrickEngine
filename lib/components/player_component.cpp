#include "brickengine/components/player_component.hpp"

PlayerComponent::PlayerComponent(int player_id, bool disabled)
    : player_id(player_id), disabled(disabled) {}

std::string PlayerComponent::getNameStatic() {
    return "PlayerComponent";
} 