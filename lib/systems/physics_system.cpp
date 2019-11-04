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
            double vy = physics->vy + (GRAVITY * mass);

            if (vy > TERMINAL_VELOCITY)
                vy = TERMINAL_VELOCITY;
            
            physics->vy = vy;
        }

        double vx = physics->vx * deltatime;
        double vy = physics->vy * deltatime;

        if (physics->vx > 0) { // Moving right
            auto collision = collisionDetector->spaceLeft(entityId, Axis::X, Direction::POSITIVE);
            auto collider = entityManager->getComponent<RectangleColliderComponent>(collision.objectId);
            double toMove = vx;

            if (collision.spaceLeft == 0){
                physics->vx = 0;
            }

            if (vx >= collision.spaceLeft){
                if(collider->isTrigger)
                    toMove = vx;
                else
                    toMove = collision.spaceLeft;
            }
            else 
                toMove = vx;

            transform->xPos = transform->xPos + toMove;
        }
        if (physics->vx < 0) { // Moving left
            auto collision = collisionDetector->spaceLeft(entityId, Axis::X, Direction::NEGATIVE);
            auto collider = entityManager->getComponent<RectangleColliderComponent>(collision.objectId);
            double toMove;

            if (collision.spaceLeft == 0) {
                physics->vx = 0;
            }

            if (vx <= collision.spaceLeft) {
                if(collider->isTrigger)
                    toMove = vx;
                else
                    toMove = collision.spaceLeft;
            }
            else
                toMove = vx;
          
            transform->xPos = transform->xPos + toMove;
        }
        if (physics->vy > 0) { // Moving down
            auto collision = collisionDetector->spaceLeft(entityId, Axis::Y, Direction::POSITIVE);
            auto collider = entityManager->getComponent<RectangleColliderComponent>(collision.objectId);
            double toMove;

            if (collision.spaceLeft == 0) {
                physics->vy = 0;
            }

            if (vy >= collision.spaceLeft)
                if(collider->isTrigger)
                    toMove = vy;
                else
                    toMove = collision.spaceLeft;
            else
                toMove = vy;

            transform->yPos = transform->yPos + toMove;
        }
        if (physics->vy < 0) { // Moving up
            auto collision = collisionDetector->spaceLeft(entityId, Axis::Y, Direction::NEGATIVE);
            auto collider = entityManager->getComponent<RectangleColliderComponent>(collision.objectId);
            double toMove;

            if (collision.spaceLeft == 0) {
                physics->vy = 0;
            }

            if (vy <= collision.spaceLeft)
                if(collider->isTrigger)
                    toMove = vy;
                else
                    toMove = collision.spaceLeft;
            else
                toMove = vy;

            transform->yPos = transform->yPos + toMove;
        }
    }
}