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
            auto collision = collisionDetector->spaceLeft(entityId, Axis::X, Direction::POSITIVE);
            auto collider = entityManager->getComponent<RectangleColliderComponent>(collision.objectId);
            double wantToMove  = physics->vx * deltatime;

            if (wantToMove >= collision.spaceLeft){
                if(collider->isTrigger)
                    transform->xPos = transform->xPos + wantToMove;
                else
                    transform->xPos = transform->xPos + collision.spaceLeft;                
            }
            else if (wantToMove < collision.spaceLeft)
                transform->xPos = transform->xPos + wantToMove;            
        }
        if (physics->vx < 0) { // Moving left
            auto collision = collisionDetector->spaceLeft(entityId, Axis::X, Direction::NEGATIVE);
            auto collider = entityManager->getComponent<RectangleColliderComponent>(collision.objectId);
            double wantToMove = physics->vx * deltatime;

            if (wantToMove <= collision.spaceLeft) {
                if(collider->isTrigger)
                    transform->xPos = transform->xPos + wantToMove;
                else
                transform->xPos = transform->xPos + collision.spaceLeft;                
            }
            else if (wantToMove > collision.spaceLeft)
                transform->xPos = transform->xPos + wantToMove;
        }
        if (physics->vy > 0) { // Moving down
            auto collision = collisionDetector->spaceLeft(entityId, Axis::Y, Direction::POSITIVE);
            auto collider = entityManager->getComponent<RectangleColliderComponent>(collision.objectId);
            double wantToMove = physics->vy * deltatime;

            if (wantToMove >= collision.spaceLeft)
                if(collider->isTrigger)
                    transform->yPos = transform->yPos + wantToMove;
                else
                    transform->yPos = transform->yPos + collision.spaceLeft;
            else if (wantToMove < collision.spaceLeft)
                transform->yPos = transform->yPos + wantToMove;
        }
        if (physics->vy < 0) { // Moving up
            auto collision = collisionDetector->spaceLeft(entityId, Axis::Y, Direction::NEGATIVE);
            auto collider = entityManager->getComponent<RectangleColliderComponent>(collision.objectId);
            double wantToMove = physics->vy * deltatime;

            if (wantToMove <= collision.spaceLeft)
                if(collider->isTrigger)
                    transform->yPos = transform->yPos + wantToMove;
                else
                    transform->yPos = transform->yPos + collision.spaceLeft;
            else if (wantToMove > collision.spaceLeft)
                transform->yPos = transform->yPos + wantToMove;
        }
    }
}