#include "brickengine/systems/physics_system.hpp"
#include "brickengine/components/physics_component.hpp"
#include "brickengine/components/transform_component.hpp"
#include <iostream>

PhysicsSystem::PhysicsSystem(std::shared_ptr<EntityManager> em) : System(em) {}

void PhysicsSystem::update(double deltatime) {
    auto entitiesWithPhysics = entityManager->getEntitiesByComponent<PhysicsComponent>();

    for(auto [entityId, physics] : *entitiesWithPhysics){
        if (physics->getKinematic()) {
            physics->setXVelocity(0);
            physics->setYVelocity(0);
            continue;
        }

        auto transform = entityManager->getComponent<TransformComponent>(entityId);
        double mass = physics->getMass();

        if (physics->getGravity()) {
            // Also do collisions
            double vy = physics->getYVelocity() + (GRAVITY * mass * deltatime);

            if (vy > TERMINAL_VELOCITY)
                vy = TERMINAL_VELOCITY;

            physics->setYVelocity(vy);
        }

        double x = transform->getXPos() + (physics->getXVelocity() * deltatime);
        double y = transform->getYPos() + (physics->getYVelocity() * deltatime);

        transform->setXPos(x);
        transform->setYPos(y);
    }
}