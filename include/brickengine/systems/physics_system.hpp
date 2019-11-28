#ifndef FILE_PHYSICS_SYSTEM_HPP
#define FILE_PHYSICS_SYSTEM_HPP

#include <memory>
#include "brickengine/entities/entity_manager.hpp"
#include "brickengine/collision_detector.hpp"
#include "brickengine/systems/system.hpp"

class PhysicsSystem : public System {
public:
    PhysicsSystem(std::shared_ptr<CollisionDetector> cd, std::shared_ptr<EntityManager> em, double &delta_time_modifier);
    void update(double deltatime);
    void updateChildren(int parentId);
private:
    static constexpr double HORIZONTAL_DRAG = 200;
    static constexpr double GRAVITY = 21.04;
    static constexpr double TERMINAL_VELOCITY = 1000;

    std::shared_ptr<CollisionDetector> collisionDetector;

    double &delta_time_modifier;
};

#endif // FILE_PHYSICS_SYSTEM_HPP