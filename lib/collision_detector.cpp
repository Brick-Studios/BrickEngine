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

CollisionDetector::CollisionDetector(std::shared_ptr<EntityManager> em) : entityManager(em) {}

double CollisionDetector::spaceLeft(int entity, Axis axis, Direction direction) {
    // We only support rectangles
    auto entityRectCollider = entityManager->getComponent<RectangleColliderComponent>(entity);
    auto [ entity_position, entity_scale ] = entityManager->getAbsoluteTransform(entity);

    auto collidableEntities = entityManager->getEntitiesByComponent<RectangleColliderComponent>();
    auto children = entityManager->getChildren(entity);
    auto parent = entityManager->getParent(entity);

    double spaceLeft = 0; // Distance to the closed object
    if(direction == Direction::NEGATIVE){
        spaceLeft = std::numeric_limits<double>::lowest();
    } else {
        spaceLeft = std::numeric_limits<double>::infinity();
    }
    
    for(auto& [ other_id, collider ] : *collidableEntities) {
        // You cannot collide with family
        if (parent && *parent == other_id) continue;
        if (children.count(other_id)) continue;
        if (other_id == entity) continue;

        auto [ other_position, other_scale ] = entityManager->getAbsoluteTransform(other_id);

        if(axis == Axis::X) {
            int yStartEntity = entity_position.y - ((entity_scale.y * entityRectCollider->yScale) / 2);
            int yEndEntity = entity_position.y + ((entity_scale.y * entityRectCollider->yScale) / 2);
            int yStartCollidable = other_position.y - ((other_scale.y * collider->yScale) / 2);
            int yEndCollidable = other_position.y + ((other_scale.y * collider->yScale) / 2);

            if(direction == Direction::POSITIVE) { // Right
                /**
                    * If (entiteit x+w >= collidable x) && (check entiteit y-y+h in range collidable y-y+h)
                    **/

                if(yStartEntity < yEndCollidable && yStartCollidable < yEndEntity) {
                    // Entities align on y-axis
                    double opposibleColliderHitwall = other_position.x - ((other_scale.x * collider->xScale) / 2);
                    double entityColliderHitwall = entity_position.x + ((entity_scale.x * entityRectCollider->xScale) / 2);

                    double difference = opposibleColliderHitwall - entityColliderHitwall;

                    if(difference >= 0 && spaceLeft > difference) {
                        spaceLeft = difference;
                    }
                }
            } else if(direction == Direction::NEGATIVE) { // Left
                /**
                    * If (entiteit x <= collidable x+w) && (check entiteit y-y+h in range collidable y-y+h)
                **/

                if(yStartEntity < yEndCollidable && yStartCollidable < yEndEntity) {
                    // Entities align on y-axiss
                    double opposibleColliderHitwall = other_position.x + ((other_scale.x * collider->xScale) / 2);
                    double entityColliderHitwall = entity_position.x - ((entity_scale.x * entityRectCollider->xScale) / 2);
                    
                    double difference = opposibleColliderHitwall - entityColliderHitwall;

                    if(difference <= 0 && spaceLeft < difference){
                        spaceLeft = difference;
                    }
                }
            }
        } else if(axis == Axis::Y) {
            int xStartEntity = entity_position.x - ((entity_scale.x * entityRectCollider->xScale) / 2);
            int xEndEntity = entity_position.x + ((entity_scale.x * entityRectCollider->xScale) / 2);
            int xStartCollidable = other_position.x - ((other_scale.x * collider->xScale) / 2);
            int xEndCollidable = other_position.x + ((other_scale.x * collider->xScale) / 2);

            if(direction == Direction::POSITIVE) { // Down
                /**
                    * If (check entiteit x-x+w in range collidable x-x+w) && (entiteit y+h >= collidable y)
                    **/
                if(xStartEntity < xEndCollidable && xStartCollidable < xEndEntity) {
                    // Entities align on x-axis
                    double opposibleColliderHitwall = other_position.y - ((other_scale.y * collider->yScale) / 2);
                    double entityColliderHitwall = entity_position.y + ((entity_scale.y * entityRectCollider->yScale) / 2);
                    
                    double difference = opposibleColliderHitwall - entityColliderHitwall;

                    if(difference >= 0 && spaceLeft > difference){
                        spaceLeft = difference;
                    }
                }
            } else if(direction == Direction::NEGATIVE) { // Up
                /**
                    * If (check entiteit x-x+w in range collidable x-x+w) && (entiteit y <= collidable y+h)
                    **/
                if(xStartEntity < xEndCollidable && xStartCollidable < xEndEntity) {
                    // Entities align on x-axis
                    double opposibleColliderHitwall = other_position.y + ((other_scale.y * collider->yScale) / 2);
                    double entityColliderHitwall = entity_position.y - ((entity_scale.y * entityRectCollider->yScale) / 2);

                    double difference = opposibleColliderHitwall - entityColliderHitwall;

                    if(difference <= 0 && spaceLeft < difference){
                        spaceLeft = difference;
                    }
                } 
            }
        }        
    }    
    return spaceLeft;
}

#endif // FILE_COLLISION_DETECTOR_HPP