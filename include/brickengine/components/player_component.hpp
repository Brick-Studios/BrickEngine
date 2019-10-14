#ifndef FILE_PLAYER_COMPONENT_HPP
#define FILE_PLAYER_COMPONENT_HPP

#include "brickengine/components/component_impl.hpp"

class PlayerComponent : public ComponentImpl<PlayerComponent> {
public:
    PlayerComponent() = default;
    static std::string getNameStatic();
};

#endif // FILE_PLAYER_COMPONENT_HPP