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
            double vy = physics->vy + (GRAVITY * mass);

            if (vy > TERMINAL_VELOCITY)
                vy = TERMINAL_VELOCITY;
            
            physics->vy = vy;
        }

        double vx = physics->vx * deltatime;
        double vy = physics->vy * deltatime;
        if (physics->vx > 0) { // Moving right
            if (physics->flipXDirection)
                transform->xDirection = Direction::POSITIVE;

            double spaceLeft = getSpaceLeftFromEntity(entityId, Axis::X, Direction::POSITIVE);
            
            if (spaceLeft != 0) {
                double wantToMove = vx;
                double toMove = (wantToMove >= spaceLeft) ? spaceLeft : wantToMove;

                transform->xPos = transform->xPos + toMove;
            }
            else {
                physics->vx = 0;
            }
        }
        if (physics->vx < 0) { // Moving left
            if (physics->flipXDirection)
                transform->xDirection = Direction::NEGATIVE;

            double spaceLeft = getSpaceLeftFromEntity(entityId, Axis::X, Direction::NEGATIVE);

            if (spaceLeft != 0) {
                double wantToMove = vx;
                double toMove = (wantToMove <= spaceLeft) ? spaceLeft : wantToMove;

                transform->xPos = transform->xPos + toMove;
            } else {
                physics->vx = 0;
            }
        }
        if (physics->vy > 0) { // Moving down
            if (physics->flipYDirection)
                transform->yDirection = Direction::POSITIVE;

            double spaceLeft = getSpaceLeftFromEntity(entityId, Axis::Y, Direction::POSITIVE);

            if (spaceLeft != 0) {
                double wantToMove = vy;
                double toMove = (wantToMove >= spaceLeft) ? spaceLeft : wantToMove;

                transform->yPos = transform->yPos + toMove;
            }
            else {
                physics->vy = 0;
            }
        }
        if (physics->vy < 0) { // Moving up
            if (physics->flipYDirection)
                transform->yDirection = Direction::NEGATIVE;

            double spaceLeft = getSpaceLeftFromEntity(entityId, Axis::Y, Direction::NEGATIVE);

            if (spaceLeft != 0) {
                double wantToMove = vy;
                double toMove = (wantToMove <= spaceLeft) ? spaceLeft : wantToMove;

                transform->yPos = transform->yPos + toMove;
            } else {
                physics->vy = 0;
            }
        }
        updateChildren(entityId);
    }
}

void PhysicsSystem::updateChildren(int parentId) {
    auto transformParent = entityManager->getComponent<TransformComponent>(parentId);
    auto children = entityManager->getChildren(parentId);
    for (const int& child : children) {
        auto transformChild = entityManager->getComponent<TransformComponent>(child);

        if (transformChild->xDirection != transformParent->xDirection) {
            transformChild->xPos *= -1;
        }
        if (transformChild->yDirection != transformParent->yDirection) {
            transformChild->yPos *= -1;
        }

        transformChild->xDirection = transformParent->xDirection;
        transformChild->yDirection = transformParent->yDirection;

        updateChildren(child);
    }
}

double PhysicsSystem::getSpaceLeftFromEntity(int entityId, Axis axis, Direction direction) {
    double leastAmountOfSpace = collisionDetector->spaceLeft(entityId, axis, direction);

    auto children = entityManager->getChildren(entityId);
    for (const int& child : children) {
        double spaceLeft = getSpaceLeftFromEntity(child, axis, direction);
        if (direction == Direction::NEGATIVE && spaceLeft > leastAmountOfSpace)
            leastAmountOfSpace = spaceLeft;
        else if (direction == Direction::POSITIVE && spaceLeft < leastAmountOfSpace)
            leastAmountOfSpace = spaceLeft;
    }

    return leastAmountOfSpace;
}