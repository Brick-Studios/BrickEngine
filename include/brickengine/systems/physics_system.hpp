#ifndef FILE_PHYSICS_SYSTEM_HPP
#define FILE_PHYSICS_SYSTEM_HPP

#include <memory>
#include "brickengine/entities/entity_manager.hpp"
#include "brickengine/systems/system.hpp"

class PhysicsSystem : public System {
public:
    PhysicsSystem(std::shared_ptr<EntityManager>);
    void update(double deltatime);
};

#endif // FILE_PHYSICS_SYSTEM_HPP