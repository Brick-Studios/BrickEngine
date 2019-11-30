#ifndef FILE_PHYSICS_SYSTEM_HPP
#define FILE_PHYSICS_SYSTEM_HPP

#include <memory>
#include "brickengine/entities/entity_manager.hpp"
#include "brickengine/collision_detector_2.hpp"
#include "brickengine/systems/system.hpp"

class PhysicsSystem : public System {
public:
    PhysicsSystem(CollisionDetector2& cd, std::shared_ptr<EntityManager> em);
    void update(double deltatime);
private:
    static constexpr double HORIZONTAL_DRAG = 200;
    static constexpr double GRAVITY = 21.04;
    static constexpr double TERMINAL_VELOCITY = 1000;

    CollisionDetector2& collision_detector;

    void updateDiscrete(TransformComponent& transform, double vx, double vy);
    void updateContinuous(int entity_id, TransformComponent& transform, PhysicsComponent& physics,
                          double vx, double vy);
    void updateDirection(int enity_id, TransformComponent& transform, PhysicsComponent& physics);
    void updateChildren(int parentId);
};

#endif // FILE_PHYSICS_SYSTEM_HPP