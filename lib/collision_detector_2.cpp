#include "brickengine/collision_detector_2.hpp"
#include "brickengine/components/colliders/rectangle_collider_component.hpp"
#include "brickengine/components/physics_component.hpp"

std::vector<DiscreteCollision> CollisionDetector2::detectDiscreteCollision(int entity_id) {
    // Entity
    auto entity_collider = em.getComponent<RectangleColliderComponent>(entity_id);
    auto [ entity_position, entity_scale ] = em.getAbsoluteTransform(entity_id);
    auto entity_parent = em.getParent(entity_id);
    auto entity_children = em.getChildren(entity_id);

    auto opposite_entities_with_collider = em.getEntitiesByComponent<RectangleColliderComponent>();

    std::vector<DiscreteCollision> collisions;

    for (auto& [ opposite_id, opposite_collider] : opposite_entities_with_collider) {
        auto [ opposite_position, opposite_scale ] = em.getAbsoluteTransform(opposite_id);
        // Can't collide with family
        if (entity_parent && *entity_parent == opposite_id) continue;
        if (entity_children.count(opposite_id)) continue;

        double entity_left = entity_position.x + ((entity_scale.x * entity_collider->x_scale) / 2);
        double entity_right = entity_position.x - ((entity_scale.x * entity_collider->x_scale) / 2);
        double entity_down = entity_position.y + ((entity_scale.y * entity_collider->y_scale) / 2);
        double entity_up = entity_position.y - ((entity_scale.y * entity_collider->y_scale) / 2);

        double opposible_left = opposite_position.x - ((opposite_scale.x * opposite_collider->x_scale) / 2);
        double opposible_right = opposite_position.x + ((opposite_scale.x * opposite_collider->x_scale) / 2);
        double opposible_down = opposite_position.y - ((opposite_scale.y * opposite_collider->y_scale) / 2);
        double opposible_up = opposite_position.y + ((opposite_scale.y * opposite_collider->y_scale) / 2);

        // Check if you are inside the x and y of the collidable
        if(entity_left >= opposible_left 
            && entity_right <= opposible_right
            && entity_down >= opposible_down
            && entity_up <= opposible_up) {
            collisions.emplace_back(EntityWithIsTrigger(entity_id, entity_collider->is_trigger),
                                    EntityWithIsTrigger(opposite_id, opposite_collider->is_trigger));
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

        auto [ other_position, other_scale ] = em.getAbsoluteTransform(opposite_id);

        if (axis == Axis::X) {
            int entity_y_start = entity_position.y - ((entity_scale.y * entity_collider->y_scale) / 2);
            int entity_y_end = entity_position.y + ((entity_scale.y * entity_collider->y_scale) / 2);
            int opposite_y_start = other_position.y - ((other_scale.y * opposite_collider->y_scale) / 2);
            int opposite_y_end = other_position.y + ((other_scale.y * opposite_collider->y_scale) / 2);

            if (direction == Direction::POSITIVE) { // Right
                if (entity_y_start < opposite_y_end && opposite_id < entity_y_end) {
                    double opposite_hit_wall = other_position.x - ((other_scale.x * opposite_collider->x_scale) / 2);
                    double entity_hit_wall = entity_position.x + ((entity_scale.x * entity_collider->x_scale) / 2);

                    double difference = opposite_hit_wall - entity_hit_wall;

                    if(difference >= 0 && collision.space_left > difference) {
                        collision.space_left = difference;
                        collision.opposite = EntityWithIsTrigger(opposite_id, opposite_collider);
                    }
                }
            } else if (direction == Direction::NEGATIVE) { // Left
                if (entity_y_start < entity_y_end && opposite_y_start < opposite_y_end) {
                    double opposite_hit_wall = other_position.x + ((other_scale.x * opposite_collider->x_scale) / 2);
                    double entity_hit_wall = entity_position.x - ((entity_scale.x * entity_collider->x_scale) / 2);

                    double difference = opposite_hit_wall - entity_hit_wall;

                    if (difference <= 0 && collision.space_left < difference) {
                        collision.space_left = difference;
                        collision.opposite = EntityWithIsTrigger(opposite_id, opposite_collider);
                    }
                }
            }
        } else if (axis == Axis::Y) {
            int entity_x_start = entity_position.x - ((entity_scale.x * entity_collider->x_scale) / 2);
            int entity_x_end = entity_position.x + ((entity_scale.x * entity_collider->x_scale) / 2);
            int opposite_x_start = other_position.x - ((other_scale.x * opposite_collider->x_scale) / 2);
            int opposite_x_end = other_position.x + ((other_scale.x * opposite_collider->x_scale) / 2);

            if (direction == Direction::POSITIVE) { // Down
                if (entity_x_start < entity_x_end && opposite_x_start < opposite_x_end) {
                    double opposite_hit_wall = other_position.y - ((other_scale.y * opposite_collider->y_scale) / 2);
                    double entity_hit_wall = entity_position.y + ((entity_scale.y * entity_collider->y_scale) / 2);

                    double difference = opposite_hit_wall - entity_hit_wall;

                    if (difference >= 0 && collision.space_left > difference) {
                        collision.space_left = difference;
                        collision.opposite = EntityWithIsTrigger(opposite_id, opposite_collider);
                    }
                }
            } else if (direction == Direction::NEGATIVE) { // Up
                if(entity_x_start < entity_x_end && opposite_x_start < opposite_x_end) {
                    double opposite_hit_wall = other_position.y + ((other_scale.y * opposite_collider->y_scale) / 2);
                    double entity_hit_wall = entity_position.y - ((entity_scale.y * entity_collider->y_scale) / 2);

                    double difference = opposite_hit_wall - entity_hit_wall;

                    if (difference <= 0 && collision.space_left < difference) {
                        collision.space_left = difference;
                        collision.opposite = EntityWithIsTrigger(opposite_id, opposite_collider);
                    }
                } 
            }
        }        
    }    
    return collision;
}
