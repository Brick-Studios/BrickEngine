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
        if (physics->kinematic != Kinematic::IS_NOT_KINEMATIC) {
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
            if (physics->flipX)
                transform->xDirection = Direction::POSITIVE;

            auto collision = collisionDetector->spaceLeft(entityId, Axis::X, Direction::POSITIVE);
            
            if (collision.spaceLeft == 0){
                physics->vx = 0;
            } else {
                double toMove = vx;
                if (toMove >= collision.spaceLeft){
                    if(!collision.isTrigger)
                        toMove = collision.spaceLeft;
                }
                else 
                    toMove = vx;

                transform->xPos = transform->xPos + toMove;
            }
        }
        if (physics->vx < 0) { // Moving left
            if (physics->flipX)
                transform->xDirection = Direction::NEGATIVE;

            auto collision = collisionDetector->spaceLeft(entityId, Axis::X, Direction::NEGATIVE);
            
            if (collision.spaceLeft == 0){
                physics->vx = 0;
            } else {
                double toMove = vx;
                if (toMove <= collision.spaceLeft){
                    if(!collision.isTrigger)
                        toMove = collision.spaceLeft;
                }
                else 
                    toMove = vx;

                transform->xPos = transform->xPos + toMove;
            }
        }
        if (physics->vy > 0) { // Moving down
            if (physics->flipY)
                transform->yDirection = Direction::POSITIVE;

            auto collision = collisionDetector->spaceLeft(entityId, Axis::Y, Direction::POSITIVE);
            
            if (collision.spaceLeft == 0){
                physics->vy = 0;
            } else {
                double toMove = vy;
                if (toMove >= collision.spaceLeft){
                    if(!collision.isTrigger)
                        toMove = collision.spaceLeft;
                }
                else 
                    toMove = vy;

                transform->yPos = transform->yPos + toMove;
            }
        }
        if (physics->vy < 0) { // Moving up
            if (physics->flipY)
                transform->yDirection = Direction::NEGATIVE;

            auto collision = collisionDetector->spaceLeft(entityId, Axis::Y, Direction::NEGATIVE);
            
            if (collision.spaceLeft == 0){
                physics->vy = 0;
            } else {
                double toMove = vy;
                if (toMove <= collision.spaceLeft){
                    if(!collision.isTrigger)
                        toMove = collision.spaceLeft;
                }
                else 
                    toMove = vy;

                transform->yPos = transform->yPos + toMove;
            }
        }
        updateChildren(entityId);
    }
}

void PhysicsSystem::updateChildren(int parentId) {
    auto transformParent = entityManager->getComponent<TransformComponent>(parentId);
    auto children = entityManager->getChildren(parentId);
    for (const int& child : children) {
        auto childPhysics = entityManager->getComponent<PhysicsComponent>(child);
        // If there is no physics in the child, nothing can happen to that child
        if (!childPhysics) continue;

        auto transformChild = entityManager->getComponent<TransformComponent>(child);

        if (childPhysics->flipX) {
            if (transformChild->xDirection != transformParent->xDirection)
                transformChild->xPos *= -1;
            transformChild->xDirection = transformParent->xDirection;
        }
        if (childPhysics->flipY) {
            if (transformChild->yDirection != transformParent->yDirection)
                transformChild->yPos *= -1;
            transformChild->yDirection = transformParent->yDirection;
        }

        updateChildren(child);
    }
}