#include "brickengine/systems/physics_system.hpp"
#include "brickengine/components/physics_component.hpp"
#include "brickengine/components/transform_component.hpp"
#include "brickengine/components/colliders/rectangle_collider_component.hpp"
#include <iostream>
#include <exception>

PhysicsSystem::PhysicsSystem(CollisionDetector2& cd, std::shared_ptr<EntityManager> em)
                : System(em), collision_detector(cd) {}

void PhysicsSystem::update(double deltatime) {
    auto entities_with_physics = entityManager->getEntitiesByComponent<PhysicsComponent>();

    for(auto [entity_id, physics] : entities_with_physics){
        if (physics->kinematic != Kinematic::IS_NOT_KINEMATIC) {
            physics->vx = 0;
            physics->vy = 0;
            continue;
        }

        auto transform = entityManager->getComponent<TransformComponent>(entity_id);
        double mass = physics->mass;

        // Gravity
        if (physics->gravity) {
            double slow_down_amount = (GRAVITY * mass) * deltatime;
            double vy_gravity = physics->vy + slow_down_amount;

            if (vy_gravity > TERMINAL_VELOCITY)
                vy_gravity = TERMINAL_VELOCITY;
            physics->vy = vy_gravity;
        }

        // Drag
        // This first part of the expresion basicly checks whether we are on the ground right now.
        // It is not 100% correct, but it does increase performance by a ton
        if (physics->drag && (physics->vy > GRAVITY || physics->vy < GRAVITY * -1) && physics->vx != 0) {
            double slow_down_amount = (HORIZONTAL_DRAG * mass) * deltatime;
            double vx_gravity;

            if (physics->vx < 0) {
                vx_gravity = physics->vx + slow_down_amount;
                if(vx_gravity < TERMINAL_VELOCITY * -1)
                    vx_gravity = TERMINAL_VELOCITY * -1;
            } else {
                vx_gravity = physics->vx - slow_down_amount;
                if(vx_gravity > TERMINAL_VELOCITY)
                    vx_gravity = TERMINAL_VELOCITY;
            }

            physics->vx = vx_gravity;
        }

        double vx = physics->vx * deltatime;
        double vy = physics->vy * deltatime;
        if (physics->collision_detection == CollisionDetectionType::Discrete) {
            updateDiscrete(entity_id, *transform, vx, vy);
        } else if (physics->collision_detection == CollisionDetectionType::Continuous) {
            updateContinuous(entity_id, *physics, *transform, vx, vy);
        } else {
            throw std::exception();
        }
    }
}

void PhysicsSystem::updateDiscrete(int entity_id, TransformComponent& transform, double vx, double vy) {
    transform.x_pos += vx;
    transform.y_pos += vy;
    updateChildren(entity_id);
}

void PhysicsSystem::updateContinuous(int entity_id, PhysicsComponent& physics, TransformComponent& transform,
                                     double vx, double vy) {
    if (physics.vx > 0) { // Moving right
        if (physics.flipX)
            transform.x_direction = Direction::POSITIVE;

        auto collision = collision_detector.detectContinuousCollision(entity_id, Axis::X, Direction::POSITIVE);

        if (collision.space_left == 0 && !collision.opposite->is_trigger) {
            physics.vx = 0;
        } else {
            double to_move = vx;
            if (to_move >= collision.space_left){
                if (!collision.opposite->is_trigger)
                    to_move = collision.space_left;
            }
            else 
                to_move = vx;

            transform.x_pos += to_move;
        }
    }
    if (physics.vx < 0) { // Moving left
        if (physics.flipX)
            transform.x_direction = Direction::NEGATIVE;

        auto collision = collision_detector.detectContinuousCollision(entity_id, Axis::X, Direction::NEGATIVE);

        if (collision.space_left == 0 && !collision.opposite->is_trigger) {
            physics.vx = 0;
        } else {
            double to_move = vx;
            if (to_move <= collision.space_left){
                if (!collision.opposite->is_trigger)
                    to_move = collision.space_left;
            }
            else 
                to_move = vx;

            transform.x_pos += to_move;
        }
    }
    if (physics.vy > 0) { // Moving down
        if (physics.flipY)
            transform.y_direction = Direction::POSITIVE;

        auto collision = collision_detector.detectContinuousCollision(entity_id, Axis::Y, Direction::POSITIVE);

        if (collision.space_left == 0 && !collision.opposite->is_trigger) {
            physics.vy = 0;
        } else {
            double to_move = vy;
            if (to_move >= collision.space_left){
                if (!collision.opposite->is_trigger)
                    to_move = collision.space_left;
            }
            else 
                to_move = vy;

            transform.y_pos += to_move;
        }
    }
    if (physics.vy < 0) { // Moving up
        if (physics.flipY)
            transform.y_direction = Direction::NEGATIVE;

        auto collision = collision_detector.detectContinuousCollision(entity_id, Axis::Y, Direction::NEGATIVE);

        if (collision.space_left == 0 && !collision.opposite->is_trigger) {
            physics.vy = 0;
        } else {
            double to_move = vy;
            if (to_move <= collision.space_left){
                if (!collision.opposite->is_trigger)
                    to_move = collision.space_left;
            }
            else 
                to_move = vy;

            transform.y_pos += to_move;
        }
    }
    updateChildren(entity_id);
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
            if (transformChild->x_direction != transformParent->x_direction)
                transformChild->x_pos *= -1;
            transformChild->x_direction = transformParent->x_direction;
        }
        if (childPhysics->flipY) {
            if (transformChild->y_direction != transformParent->y_direction)
                transformChild->y_pos *= -1;
            transformChild->y_direction = transformParent->y_direction;
        }

        updateChildren(child);
    }
}