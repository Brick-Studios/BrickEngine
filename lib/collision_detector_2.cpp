#include "brickengine/collision_detector_2.hpp"
#include "brickengine/components/colliders/rectangle_collider_component.hpp"
#include "brickengine/components/physics_component.hpp"
#include "brickengine/std/sign.hpp"
#include <cmath>

std::vector<DiscreteCollision> CollisionDetector2::detectDiscreteCollision(int entity_id) {
    // Entity
    auto entity_collider = em.getComponent<RectangleColliderComponent>(entity_id);
    auto [ entity_position, entity_scale ] = em.getAbsoluteTransform(entity_id);
    auto entity_parent = em.getParent(entity_id);
    auto entity_children = em.getChildren(entity_id);

    auto opposite_entities_with_collider = em.getEntitiesByComponent<RectangleColliderComponent>();

    std::vector<DiscreteCollision> collisions;

    for (auto& [ opposite_id, opposite_collider] : opposite_entities_with_collider) {
        // Can't collide with yourself
        if (opposite_id == entity_id) continue;
        auto [ opposite_position, opposite_scale ] = em.getAbsoluteTransform(opposite_id);
        // Can't collide with family
        if (entity_parent && *entity_parent == opposite_id) continue;
        if (entity_children.count(opposite_id)) continue;

        const double entity_half_x = (entity_scale.x * entity_collider->x_scale) / 2;
        const double entity_half_y = (entity_scale.y * entity_collider->y_scale) / 2;
        const double opposite_half_x = (opposite_scale.x * opposite_collider->x_scale) / 2;
        const double opposite_half_y = (opposite_scale.y * opposite_collider->y_scale) / 2;

        // Check if there is a collision in the x axis
        const double delta_x = entity_position.x - opposite_position.x;
        const double pos_x = (entity_half_x + opposite_half_x) - std::abs(delta_x);
        if (pos_x <= 0) continue;

        // Check if there is a collision in the y axis
        const double delta_y = entity_position.y - opposite_position.y;
        const double pos_y = (entity_half_y + opposite_half_y) - std::abs(delta_y);
        if (pos_y <= 0) continue;
        
        // x axis collision
        if (pos_x < pos_y) {
            const double sign_x = sign(delta_x);
            Position position = Position(opposite_position.x + (opposite_half_x * sign_x), entity_position.y);
            Position delta = Position(pos_x * sign_x, 0);
            Position normal = Position(sign_x, 0);
            collisions.emplace_back(
                EntityWithIsTrigger(entity_id, entity_collider->is_trigger),
                EntityWithIsTrigger(opposite_id, opposite_collider->is_trigger),
                position, delta, normal);
        } else { // y axis collision
            const double sign_y = sign(delta_y);
            Position position = Position(entity_position.x, opposite_position.y + (opposite_half_y * sign_y));
            Position delta = Position(0, pos_y * sign_y);
            Position normal = Position(0, sign_y);
            collisions.emplace_back(
                EntityWithIsTrigger(entity_id, entity_collider->is_trigger),
                EntityWithIsTrigger(opposite_id, opposite_collider->is_trigger),
                position, delta, normal);
        }
    }
    return collisions;
}

ContinuousCollision CollisionDetector2::detectContinuousCollision(int entity_id, Axis axis, Direction direction) {
    // We only support rectangles
    auto entity_collider = em.getComponent<RectangleColliderComponent>(entity_id);
    auto [ entity_position, entity_scale ] = em.getAbsoluteTransform(entity_id);
    auto entity_children = em.getChildren(entity_id);
    auto entity_parent = em.getParent(entity_id);

    auto opposite_entities_with_collider = em.getEntitiesByComponent<RectangleColliderComponent>();

    double space_left_start_value;
    if (direction == Direction::NEGATIVE)
        space_left_start_value = std::numeric_limits<double>::lowest();
    else
        space_left_start_value = std::numeric_limits<double>::infinity();

    ContinuousCollision collision { EntityWithIsTrigger(entity_id, entity_collider->is_trigger),
                                    std::nullopt, space_left_start_value };

    for (auto& [ opposite_id, opposite_collider ] : opposite_entities_with_collider) {
        // You cannot collide with family
        if (entity_parent && *entity_parent == opposite_id) continue;
        if (entity_children.count(opposite_id)) continue;
        if (opposite_id == entity_id) continue;
        if (opposite_collider->is_trigger) continue;

        auto [ opposite_position, opposite_scale ] = em.getAbsoluteTransform(opposite_id);

        if (axis == Axis::X) {
            int entity_y_start = entity_position.y - ((entity_scale.y * entity_collider->y_scale) / 2);
            int entity_y_end = entity_position.y + ((entity_scale.y * entity_collider->y_scale) / 2);
            int opposite_y_start = opposite_position.y - ((opposite_scale.y * opposite_collider->y_scale) / 2);
            int opposite_y_end = opposite_position.y + ((opposite_scale.y * opposite_collider->y_scale) / 2);

            if (direction == Direction::POSITIVE) { // Right
                if (entity_y_start < opposite_y_end && opposite_y_start < entity_y_end) {
                    double opposite_hit_wall = opposite_position.x - ((opposite_scale.x * opposite_collider->x_scale) / 2);
                    double entity_hit_wall = entity_position.x + ((entity_scale.x * entity_collider->x_scale) / 2);

                    double difference = opposite_hit_wall - entity_hit_wall;

                    if(difference >= 0 && collision.space_left > difference) {
                        collision.space_left = difference;
                        collision.opposite = EntityWithIsTrigger(opposite_id, opposite_collider->is_trigger);
                    }
                }
            } else if (direction == Direction::NEGATIVE) { // Left
                if (entity_y_start < opposite_y_end && opposite_y_start < entity_y_end) {
                    double opposite_hit_wall = opposite_position.x + ((opposite_scale.x * opposite_collider->x_scale) / 2);
                    double entity_hit_wall = entity_position.x - ((entity_scale.x * entity_collider->x_scale) / 2);

                    double difference = opposite_hit_wall - entity_hit_wall;

                    if (difference <= 0 && collision.space_left < difference) {
                        collision.space_left = difference;
                        collision.opposite = EntityWithIsTrigger(opposite_id, opposite_collider->is_trigger);
                    }
                }
            }
        } else if (axis == Axis::Y) {
            int entity_x_start = entity_position.x - ((entity_scale.x * entity_collider->x_scale) / 2);
            int entity_x_end = entity_position.x + ((entity_scale.x * entity_collider->x_scale) / 2);
            int opposite_x_start = opposite_position.x - ((opposite_scale.x * opposite_collider->x_scale) / 2);
            int opposite_x_end = opposite_position.x + ((opposite_scale.x * opposite_collider->x_scale) / 2);

            if (direction == Direction::POSITIVE) { // Down
                if (entity_x_start < opposite_x_end && opposite_x_start < entity_x_end) {
                    double opposite_hit_wall = opposite_position.y - ((opposite_scale.y * opposite_collider->y_scale) / 2);
                    double entity_hit_wall = entity_position.y + ((entity_scale.y * entity_collider->y_scale) / 2);

                    double difference = opposite_hit_wall - entity_hit_wall;

                    if (difference >= 0 && collision.space_left > difference) {
                        collision.space_left = difference;
                        collision.opposite = EntityWithIsTrigger(opposite_id, opposite_collider->is_trigger);
                    }
                }
            } else if (direction == Direction::NEGATIVE) { // Up
                if(entity_x_start < opposite_x_end && opposite_x_start < entity_x_end) {
                    double opposite_hit_wall = opposite_position.y + ((opposite_scale.y * opposite_collider->y_scale) / 2);
                    double entity_hit_wall = entity_position.y - ((entity_scale.y * entity_collider->y_scale) / 2);

                    double difference = opposite_hit_wall - entity_hit_wall;

                    if (difference <= 0 && collision.space_left < difference) {
                        collision.space_left = difference;
                        collision.opposite = EntityWithIsTrigger(opposite_id, opposite_collider->is_trigger);
                    }
                } 
            }
        }        
    }    
    return collision;
}
