#include "brickengine/systems/physics_system.hpp"
#include "brickengine/components/physics_component.hpp"
#include "brickengine/components/transform_component.hpp"
#include <iostream>

PhysicsSystem::PhysicsSystem(std::shared_ptr<EntityManager> em) : System(em) {}

void PhysicsSystem::update(double deltatime) {
    auto entitiesWithPhysics = entityManager->getEntitiesByComponent<PhysicsComponent>();

    for(auto [entityId, physics] : *entitiesWithPhysics){
        if (physics->kinematic) {
            physics->vx = 0;
            physics->vy = 0;
            continue;
        }

        auto transform = entityManager->getComponent<TransformComponent>(entityId);
        double mass = physics->mass;

        if (physics->gravity) {
            // Also do collisions
            double vy = physics->vy + (GRAVITY * mass * deltatime);

            if (vy > TERMINAL_VELOCITY)
                vy = TERMINAL_VELOCITY;

            physics->vy = vy;
        }

        double x = transform->xPos + (physics->vx * deltatime);
        double y = transform->yPos + (physics->vy * deltatime);

        transform->xPos = x;
        transform->yPos = y;
    }
}