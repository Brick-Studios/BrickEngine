#ifndef FILE_PHYSICS_SYSTEM_HPP
#define FILE_PHYSICS_SYSTEM_HPP

#include <memory>
#include "brickengine/entities/entity_manager.hpp"
#include "brickengine/collision_detector.hpp"
#include "brickengine/systems/system.hpp"

class PhysicsSystem : public System {
public:
    PhysicsSystem(std::shared_ptr<CollisionDetector> cd, std::shared_ptr<EntityManager> em);
    void update(double deltatime);
private:
    static constexpr double GRAVITY = 1;
    static constexpr double TERMINAL_VELOCITY = 200;

    std::shared_ptr<CollisionDetector> collisionDetector;
};

#endif // FILE_PHYSICS_SYSTEM_HPP