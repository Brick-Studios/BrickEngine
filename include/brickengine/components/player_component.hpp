#ifndef FILE_PLAYER_COMPONENT_HPP
#define FILE_PLAYER_COMPONENT_HPP

#include "brickengine/components/component_impl.hpp"

class PlayerComponent : public ComponentImpl<PlayerComponent> {
public:
    PlayerComponent(int playerId);
    static std::string getNameStatic();

    // Data
    int playerId;
};

#endif // FILE_PLAYER_COMPONENT_HPP 