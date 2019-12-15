#include "brickengine/systems/physics_system.hpp"
#include "brickengine/components/physics_component.hpp"
#include "brickengine/components/transform_component.hpp"
#include "brickengine/components/colliders/rectangle_collider_component.hpp"
#include "brickengine/std/floating_point_comparer.hpp"
#include <iostream>
#include <exception>
#include <tuple>

PhysicsSystem::PhysicsSystem(CollisionDetector2& cd, std::shared_ptr<EntityManager> em, double &delta_time_modifier)
                : System(em), collision_detector(cd), delta_time_modifier(delta_time_modifier) {}

void PhysicsSystem::update(double deltatime) {
    auto entities_with_physics = entityManager->getEntitiesByComponent<PhysicsComponent>();

    std::for_each(entities_with_physics.begin(), entities_with_physics.end(), [](const auto& lhs) {
        auto& lhs_physics = lhs.second;
        std::cout << &lhs_physics->collision_detection << std::endl;
    });

    std::stable_sort(entities_with_physics.begin(), entities_with_physics.end(), [](const auto& lhs, const auto& rhs) {
        auto& lhs_physics = lhs.second;
        auto& rhs_physics = rhs.second;
        std::cout << &lhs_physics->collision_detection << std::endl;
        std::cout << &rhs_physics->collision_detection << std::endl;
        return (lhs_physics->collision_detection.isDiscrete() && !lhs_physics->collision_detection.isContinuous()) > !rhs_physics->collision_detection.isDiscrete();
    });

    for(auto [entity_id, physics] : entities_with_physics){
        if (physics->kinematic != Kinematic::IS_NOT_KINEMATIC) {
            physics->vx = 0;
            physics->vy = 0;
            continue;
        }

        auto transform = entityManager->getComponent<TransformComponent>(entity_id);
        const double mass = physics->mass;

        // Gravity
        const ContinuousCollision collision = collision_detector.detectContinuousCollision(entity_id, Axis::Y, Direction::POSITIVE);
        if (!FloatingPointComparer::is_equal_to_zero(collision.space_left)) {
            if (physics->gravity) {
                double slow_down_amount = (GRAVITY * mass) * deltatime;
                double vy_gravity = physics->vy + slow_down_amount;

                if (vy_gravity > TERMINAL_VELOCITY)
                    vy_gravity = TERMINAL_VELOCITY;
                physics->vy = vy_gravity;
            }
        }

        // Drag
        // This first part of the expresion basicly checks whether we are on the ground right now.
        // It is not 100% correct, but it does increase performance by a ton
        if (physics->drag && (physics->vy > GRAVITY || physics->vy < GRAVITY * -1) && !FloatingPointComparer::is_equal_to_zero(physics->vx)) {
            double horizontal_drag_with_modifier = HORIZONTAL_DRAG / delta_time_modifier;
            const double slow_down_amount = (horizontal_drag_with_modifier * mass) * deltatime;
            double vx_drag;

            if (physics->vx < 0) {
                vx_drag = physics->vx + slow_down_amount;
                if(vx_drag < TERMINAL_VELOCITY * -1)
                    vx_drag = TERMINAL_VELOCITY * -1;
            } else {
                vx_drag = physics->vx - slow_down_amount;
                if(vx_drag > TERMINAL_VELOCITY)
                    vx_drag = TERMINAL_VELOCITY;
            }

            physics->vx = vx_drag;
        }

        const double vx = physics->vx * deltatime;
        const double vy = physics->vy * deltatime;
        if (physics->collision_detection.isContinuous()) {
            updateContinuous(entity_id, *transform, *physics, vx, vy);
        } else if (physics->collision_detection.isDiscrete()) {
            updateDiscrete(*transform, vx, vy);
        }
        updateDirection(entity_id, *transform, *physics);
    }
}

void PhysicsSystem::updateDirection(int entity_id, TransformComponent& transform, PhysicsComponent& physics) {
    if (physics.flipX) {
        if (physics.vx > 0) // Moving right
            transform.x_direction = Direction::POSITIVE;
        if (physics.vx < 0) // Moving left
            transform.x_direction = Direction::NEGATIVE;
    }
    if (physics.flipY) {
        if (physics.vy > 0) // Moving down
            transform.y_direction = Direction::POSITIVE;
        if (physics.vy < 0) // Moving up
            transform.y_direction = Direction::NEGATIVE;
    }

    updateChildren(entity_id);
}

void PhysicsSystem::updateDiscrete(TransformComponent& transform, double vx, double vy) {
    transform.x_pos += vx;
    transform.y_pos += vy;
}

void PhysicsSystem::updateContinuous(int entity_id, TransformComponent& transform, PhysicsComponent& physics,
                                     double vx, double vy) {
    if (physics.vx > 0) { // Moving right
        const auto collision = collision_detector.detectContinuousCollision(entity_id, Axis::X, Direction::POSITIVE);

        if (FloatingPointComparer::is_equal_to_zero(collision.space_left)) {
            physics.vx = 0;
        } else {
            double to_move = vx;
            if (to_move > collision.space_left || FloatingPointComparer::is_equal_to_zero(collision.space_left)) {
                to_move = collision.space_left;
                physics.vx = 0;
            }
            else 
                to_move = vx;

            transform.x_pos += to_move;
        }
    }
    if (physics.vx < 0) { // Moving left
        const auto collision = collision_detector.detectContinuousCollision(entity_id, Axis::X, Direction::NEGATIVE);

        if (FloatingPointComparer::is_equal_to_zero(collision.space_left)) {
            physics.vx = 0;
        } else {
            double to_move = vx;
            if (to_move < collision.space_left || FloatingPointComparer::is_equal_to_zero(collision.space_left)){
                to_move = collision.space_left;
                physics.vx = 0;
            }
            else 
                to_move = vx;

            transform.x_pos += to_move;
        }
    }
    if (physics.vy > 0) { // Moving down
        const auto collision = collision_detector.detectContinuousCollision(entity_id, Axis::Y, Direction::POSITIVE);

        if (FloatingPointComparer::is_equal_to_zero(collision.space_left)) {
            physics.vy = 0;
        } else {
            double to_move = vy;
            if (to_move > collision.space_left || FloatingPointComparer::is_equal_to_zero(collision.space_left)){
                to_move = collision.space_left;
                physics.vy = 0;
            }
            else 
                to_move = vy;

            transform.y_pos += to_move;
        }
    }
    if (physics.vy < 0) { // Moving up
        const auto collision = collision_detector.detectContinuousCollision(entity_id, Axis::Y, Direction::NEGATIVE);

        if (FloatingPointComparer::is_equal_to_zero(collision.space_left)) {
            physics.vy = 0;
        } else {
            double to_move = vy;
            if (to_move < collision.space_left || FloatingPointComparer::is_equal_to_zero(collision.space_left)){
                to_move = collision.space_left;
                physics.vy = 0;
            }
            else 
                to_move = vy;

            transform.y_pos += to_move;
        }
    }
    updateChildren(entity_id);
}

void PhysicsSystem::updateChildren(int parentId) {
    const auto transformParent = entityManager->getComponent<TransformComponent>(parentId);
    const auto children = entityManager->getChildren(parentId);
    for (const int& child : children) {
        const auto childPhysics = entityManager->getComponent<PhysicsComponent>(child);
        // If there is no physics in the child, nothing can happen to that child
        if (!childPhysics) continue;

        const auto transformChild = entityManager->getComponent<TransformComponent>(child);

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