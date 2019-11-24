#ifndef FILE_COLLISION_DETECTOR_CPP
#define FILE_COLLISION_DETECTOR_CPP

#include <limits>
#include <map>
#include <unordered_map>

#include "brickengine/collision_detector.hpp"
#include "brickengine/enum/axis.hpp"
#include "brickengine/enum/direction.hpp"
#include "brickengine/components/colliders/rectangle_collider_component.hpp"
#include "brickengine/components/transform_component.hpp"

CollisionDetector::CollisionDetector(std::shared_ptr<EntityManager> em) : entity_manager(em) {}

void CollisionDetector::clearCache() {
    space_left_cache.clear();
    trigger_cache.clear();
}

CollisionReturnValues CollisionDetector::spaceLeft(int entity, Axis axis, Direction direction) {
    if (space_left_cache.count(entity) && space_left_cache.at(entity).count(axis)
        && space_left_cache.at(entity).at(axis).count(direction)) {
        ++space_left_cache_hits;
        return space_left_cache.at(entity).at(axis).at(direction);
    }

    // We only support rectangles
    auto entity_rect_collider = entity_manager->getComponent<RectangleColliderComponent>(entity);
    auto [ entity_position, entity_scale ] = entity_manager->getAbsoluteTransform(entity);

    auto collidable_entities = entity_manager->getEntitiesByComponent<RectangleColliderComponent>();
    auto children = entity_manager->getChildren(entity);
    auto parent = entity_manager->getParent(entity);

    double space_left = 0; // Distance to the closed object
    std::optional<int> object_id = std::nullopt;
    bool is_trigger;

    if(direction == Direction::NEGATIVE){
        space_left = std::numeric_limits<double>::lowest();
    } else {
        space_left = std::numeric_limits<double>::infinity();
    }

    for(auto& [ other_id, collider ] : collidable_entities) {
        // You cannot collide with family
        if (parent && *parent == other_id) continue;
        if (children.count(other_id)) continue;
        if (other_id == entity) continue;

        ++space_left_calculated_counter;

        auto [ other_position, other_scale ] = entity_manager->getAbsoluteTransform(other_id);

        if(axis == Axis::X) {
            int yStartEntity = entity_position.y - ((entity_scale.y * entity_rect_collider->y_scale) / 2);
            int yEndEntity = entity_position.y + ((entity_scale.y * entity_rect_collider->y_scale) / 2);
            int yStartCollidable = other_position.y - ((other_scale.y * collider->y_scale) / 2);
            int yEndCollidable = other_position.y + ((other_scale.y * collider->y_scale) / 2);

            if(direction == Direction::POSITIVE) { // Right
                /**
                    * If (entiteit x+w >= collidable x) && (check entiteit y-y+h in range collidable y-y+h)
                    **/

                if(yStartEntity < yEndCollidable && yStartCollidable < yEndEntity) {
                    // Entities align on y-axis
                    double opposibleColliderHitwall = other_position.x - ((other_scale.x * collider->x_scale) / 2);
                    double entityColliderHitwall = entity_position.x + ((entity_scale.x * entity_rect_collider->x_scale) / 2);

                    double difference = opposibleColliderHitwall - entityColliderHitwall;

                    if(difference >= 0 && space_left > difference) {
                        space_left = difference;
                        object_id = other_id;
                        is_trigger = collider->is_trigger;
                    }
                }
            } else if(direction == Direction::NEGATIVE) { // Left
                /**
                    * If (entiteit x <= collidable x+w) && (check entiteit y-y+h in range collidable y-y+h)
                **/

                if(yStartEntity < yEndCollidable && yStartCollidable < yEndEntity) {
                    // Entities align on y-axiss
                    double opposibleColliderHitwall = other_position.x + ((other_scale.x * collider->x_scale) / 2);
                    double entityColliderHitwall = entity_position.x - ((entity_scale.x * entity_rect_collider->x_scale) / 2);
                    
                    double difference = opposibleColliderHitwall - entityColliderHitwall;

                    if(difference <= 0 && space_left < difference){
                        space_left = difference;
                        object_id = other_id;
                        is_trigger = collider->is_trigger;
                    }
                }
            }
        } else if(axis == Axis::Y) {
            int xStartEntity = entity_position.x - ((entity_scale.x * entity_rect_collider->x_scale) / 2);
            int xEndEntity = entity_position.x + ((entity_scale.x * entity_rect_collider->x_scale) / 2);
            int xStartCollidable = other_position.x - ((other_scale.x * collider->x_scale) / 2);
            int xEndCollidable = other_position.x + ((other_scale.x * collider->x_scale) / 2);

            if(direction == Direction::POSITIVE) { // Down
                /**
                    * If (check entiteit x-x+w in range collidable x-x+w) && (entiteit y+h >= collidable y)
                    **/
                if(xStartEntity < xEndCollidable && xStartCollidable < xEndEntity) {
                    // Entities align on x-axis
                    double opposibleColliderHitwall = other_position.y - ((other_scale.y * collider->y_scale) / 2);
                    double entityColliderHitwall = entity_position.y + ((entity_scale.y * entity_rect_collider->y_scale) / 2);

                    double difference = opposibleColliderHitwall - entityColliderHitwall;

                    if(difference >= 0 && space_left > difference){
                        space_left = difference;
                        object_id = other_id;
                        is_trigger = collider->is_trigger;
                    }
                }
            } else if(direction == Direction::NEGATIVE) { // Up
                /**
                    * If (check entiteit x-x+w in range collidable x-x+w) && (entiteit y <= collidable y+h)
                    **/
                if(xStartEntity < xEndCollidable && xStartCollidable < xEndEntity) {
                    // Entities align on x-axis
                    double opposibleColliderHitwall = other_position.y + ((other_scale.y * collider->y_scale) / 2);
                    double entityColliderHitwall = entity_position.y - ((entity_scale.y * entity_rect_collider->y_scale) / 2);

                    double difference = opposibleColliderHitwall - entityColliderHitwall;

                    if(difference <= 0 && space_left < difference){
                        space_left = difference;
                        object_id = other_id;
                        is_trigger = collider->is_trigger;
                    }
                } 
            }
        }        
    }    
    auto collision =  CollisionReturnValues(space_left, object_id, is_trigger);
    space_left_cache.insert({ entity, std::unordered_map<Axis, std::unordered_map<Direction, CollisionReturnValues>>() });
    space_left_cache.at(entity).insert({ axis, std::unordered_map<Direction, CollisionReturnValues>() });
    space_left_cache.at(entity).at(axis).insert({ direction, collision });
    return collision;
}

TriggerReturnValues CollisionDetector::isInTrigger(int entity){
    if (trigger_cache.count(entity)) {
        ++trigger_cache_hits;
        return trigger_cache.at(entity);
    }
    // We only support rectangles
    auto entity_rect_collider = entity_manager->getComponent<RectangleColliderComponent>(entity);
    auto entity_transform = entity_manager->getComponent<TransformComponent>(entity);
    auto parent = entity_manager->getParent(entity);
    auto children = entity_manager->getChildren(entity);

    auto collidable_entities = entity_manager->getEntitiesByComponent<RectangleColliderComponent>();

    auto values = TriggerReturnValues(false, std::nullopt);

    for(auto& [id, collider] : collidable_entities) {
        // You cannot trigger with family
        if (parent && *parent == id) continue;
        if (children.count(id)) continue;

        ++trigger_calculated_counter;
        auto transform_component = entity_manager->getComponent<TransformComponent>(id);

        if (collider->is_trigger) {
            double opposible_left = transform_component->x_pos - ((transform_component->x_scale * collider->x_scale) / 2);
            double opposible_right = transform_component->x_pos + ((transform_component->x_scale * collider->x_scale) / 2);
            double opposible_down = transform_component->y_pos - ((transform_component->y_scale * collider->y_scale) / 2);
            double opposible_up = transform_component->y_pos + ((transform_component->y_scale * collider->y_scale) / 2);

            double entity_left = entity_transform->x_pos + ((entity_transform->x_scale * entity_rect_collider->x_scale) / 2);
            double entity_right = entity_transform->x_pos - ((entity_transform->x_scale * entity_rect_collider->x_scale) / 2);
            double entity_down = entity_transform->y_pos + ((entity_transform->y_scale * entity_rect_collider->y_scale) / 2);
            double entity_up = entity_transform->y_pos - ((entity_transform->y_scale * entity_rect_collider->y_scale) / 2);

            // Check if you are inside the x and y of the collidable
            if (entity_left >= opposible_left 
                && entity_right <= opposible_right
                && entity_down >= opposible_down
                && entity_up <= opposible_up) {
                values.is_in_trigger = true;
                values.object_id = id;
            }
        }
    }
    trigger_cache.insert({ entity, values});
    return values;
}

#endif // FILE_COLLISION_DETECTOR_HPP