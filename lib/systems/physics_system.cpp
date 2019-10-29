#include "brickengine/systems/physics_system.hpp"
#include "brickengine/components/physics_component.hpp"
#include "brickengine/components/transform_component.hpp"
#include <iostream>

PhysicsSystem::PhysicsSystem(std::shared_ptr<CollisionDetector> cd, std::shared_ptr<EntityManager> em)
                : System(em), collisionDetector(cd) {}

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
            double vy = physics->vy + (GRAVITY * mass) * deltatime;

            if (vy > TERMINAL_VELOCITY)
                vy = TERMINAL_VELOCITY;
            
            physics->vy = vy;
        }

        double vx = physics->vx * deltatime;
        double vy = physics->vy * deltatime;
        if (physics->vx > 0) { // Moving right
            double spaceLeft = collisionDetector->spaceLeft(entityId, Axis::X, Direction::POSITIVE);
            double wantToMove = vx;
            double toMove = (wantToMove >= spaceLeft) ? spaceLeft : wantToMove;

            transform->xPos = transform->xPos + toMove;
        }
        if (physics->vx < 0) { // Moving left
            double spaceLeft = collisionDetector->spaceLeft(entityId, Axis::X, Direction::NEGATIVE);
            double wantToMove = vx;
            double toMove = (wantToMove <= spaceLeft) ? spaceLeft : wantToMove;

            transform->xPos = transform->xPos + toMove;
        }
        if (physics->vy > 0) { // Moving down
            double spaceLeft = collisionDetector->spaceLeft(entityId, Axis::Y, Direction::POSITIVE);
            double wantToMove = vy;
            double toMove = (wantToMove >= spaceLeft) ? spaceLeft : wantToMove;

            transform->yPos = transform->yPos + toMove;
        }
        if (physics->vy < 0) { // Moving up
            double spaceLeft = collisionDetector->spaceLeft(entityId, Axis::Y, Direction::NEGATIVE);
            double wantToMove = vy;
            double toMove = (wantToMove <= spaceLeft) ? spaceLeft : wantToMove;

            transform->yPos = transform->yPos + toMove;
        }
    }
}