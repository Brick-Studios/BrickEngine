#include "brickengine/systems/physics_system.hpp"
#include "brickengine/components/physics_component.hpp"
#include "brickengine/components/transform_component.hpp"
#include "brickengine/components/colliders/rectangle_collider_component.hpp"
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
            double vy = physics->vy + (GRAVITY * mass * deltatime);

            if (vy > TERMINAL_VELOCITY)
                vy = TERMINAL_VELOCITY;

            physics->vy = vy;
        }

        if (physics->vx > 0) { // Moving right
            auto spaceLeft = collisionDetector->spaceLeft(entityId, Axis::X, Direction::POSITIVE).first;
            auto collider = entityManager->getComponent<RectangleColliderComponent>(collisionDetector->spaceLeft(entityId, Axis::X, Direction::POSITIVE).second);
            double wantToMove  = physics->vx * deltatime;

            if (wantToMove >= spaceLeft){
                if(collider->isTrigger)
                    transform->xPos = transform->xPos + wantToMove;
                else
                    transform->xPos = transform->xPos + spaceLeft;
                
            }
            else if (wantToMove < spaceLeft)
                transform->xPos = transform->xPos + wantToMove;            
        }
        if (physics->vx < 0) { // Moving left
            double spaceLeft = collisionDetector->spaceLeft(entityId, Axis::X, Direction::NEGATIVE).first;
            auto collider = entityManager->getComponent<RectangleColliderComponent>(collisionDetector->spaceLeft(entityId, Axis::X, Direction::NEGATIVE).second);
            double wantToMove = physics->vx * deltatime;

            if (wantToMove <= spaceLeft) {
                if(collider->isTrigger)
                    transform->xPos = transform->xPos + wantToMove;
                else
                transform->xPos = transform->xPos + spaceLeft;                
            }
            else if (wantToMove > spaceLeft)
                transform->xPos = transform->xPos + wantToMove;
        }
        if (physics->vy > 0) { // Moving down
            double spaceLeft = collisionDetector->spaceLeft(entityId, Axis::Y, Direction::POSITIVE).first;
            auto collider = entityManager->getComponent<RectangleColliderComponent>(collisionDetector->spaceLeft(entityId, Axis::Y, Direction::POSITIVE).second);
            double wantToMove = physics->vy * deltatime;

            if (wantToMove >= spaceLeft)
                if(collider->isTrigger)
                    transform->yPos = transform->yPos + wantToMove;
                else
                    transform->yPos = transform->yPos + spaceLeft;
            else if (wantToMove < spaceLeft)
                transform->yPos = transform->yPos + wantToMove;
        }
        if (physics->vy < 0) { // Moving up
            double spaceLeft = collisionDetector->spaceLeft(entityId, Axis::Y, Direction::NEGATIVE).first;
            auto collider = entityManager->getComponent<RectangleColliderComponent>(collisionDetector->spaceLeft(entityId, Axis::Y, Direction::NEGATIVE).second);
            double wantToMove = physics->vy * deltatime;

            if (wantToMove <= spaceLeft)
                if(collider->isTrigger)
                    transform->yPos = transform->yPos + wantToMove;
                else
                    transform->yPos = transform->yPos + spaceLeft;
            else if (wantToMove > spaceLeft)
                transform->yPos = transform->yPos + wantToMove;
        }
    }
}