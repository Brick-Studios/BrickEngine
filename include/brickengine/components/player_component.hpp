#ifndef FILE_PLAYER_COMPONENT_HPP
#define FILE_PLAYER_COMPONENT_HPP

#include "brickengine/components/component_impl.hpp"
#include <string>

class PlayerComponent : public ComponentImpl<PlayerComponent> {
public:
    PlayerComponent(int player_id, std::string name, bool disabled = false);
    static std::string getNameStatic();

    // Data
    int player_id;
    bool disabled;
    std::string name;
};

#endif // FILE_PLAYER_COMPONENT_HPP