#include "brickengine/components/player_component.hpp"

PlayerComponent::PlayerComponent(int player_id, std::string name, bool disabled)
    : player_id(player_id), disabled(disabled), name(name) {}

std::string PlayerComponent::getNameStatic() {
    return "PlayerComponent";
} 