#ifndef FILE_ANIMATION_SYSTEM_HPP
#define FILE_ANIMATION_SYSTEM_HPP

#include "brickengine/systems/system.hpp"

class AnimationSystem : public System {
public:
    AnimationSystem(std::shared_ptr<EntityManager> em);
    void update(double deltatime);
};

#endif // FILE_ANIMATION_SYSTEM_HPP
