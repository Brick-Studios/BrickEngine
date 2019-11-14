#ifndef FILE_PLAYER_COMPONENT_HPP
#define FILE_PLAYER_COMPONENT_HPP

#include "brickengine/components/component_impl.hpp"

class PlayerComponent : public ComponentImpl<PlayerComponent> {
public:
    PlayerComponent(int player_id, bool disabled = false);
    static std::string getNameStatic();

    // Data
    int player_id;
    bool disabled;
};

#endif // FILE_PLAYER_COMPONENT_HPP