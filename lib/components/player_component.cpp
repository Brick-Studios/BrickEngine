#include "brickengine/components/player_component.hpp"

PlayerComponent::PlayerComponent(int playerId)
                    : playerId(playerId) {}

std::string PlayerComponent::getNameStatic() {
    return "PlayerComponent";
} 