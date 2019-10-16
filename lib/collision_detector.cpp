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
    //We only support squares.
    auto entityRectCollider = entityManager->getComponent<RectangleColliderComponent>(entity);
    auto entityTransform = entityManager->getComponent<TransformComponent>(entity);

    auto collidableEntities = entityManager->getEntitiesByComponent<RectangleColliderComponent>();

    double spaceLeft = 0; //Distance to the closed object
    if(direction == Direction::NEGATIVE){
        spaceLeft = -100000;
    } else {
        spaceLeft = 100000;
    }
    
    for(auto& [id, collider] : *collidableEntities) {
        auto transformComponent = entityManager->getComponent<TransformComponent>(id);

        // int zStartEntity = transformComponent->z;
        // int zEndEntity = entityRectCollider->z + entityRectCollider->zScale;
        // int zStartCollidable = transformComponent->z;
        // int zEndCollidable = transformComponent->z + transformComponent->zScale;

        if(id != entity 
        // && (zStartEntity <= zEndCollidable && zStartCollidable <= zEndEntity)
        ) {
            if(axis == Axis::X) {
                int yStartEntity = entityTransform->yPos - ((entityTransform->yScale * entityRectCollider->yScale) / 2);
                int yEndEntity = entityTransform->yPos + ((entityTransform->yScale * entityRectCollider->yScale) / 2);
                int yStartCollidable = transformComponent->yPos - ((transformComponent->yScale * collider->yScale) / 2);
                int yEndCollidable = transformComponent->yPos + ((transformComponent->yScale * collider->yScale) / 2);

                if(direction == Direction::POSITIVE) { //Right
                    /**
                     * Als (entiteit x+w >= collidable x) && (check entiteit y-y+h in range collidable y-y+h)
                     **/

                    if(yStartEntity < yEndCollidable && yStartCollidable < yEndEntity) {
                        //Entities align on y-axis
                        double opposibleColliderHitwall = transformComponent->xPos - ((transformComponent->xScale * collider->xScale) / 2);
                        double entityColliderHitwall = entityTransform->xPos + ((entityTransform->xScale * entityRectCollider->xScale) / 2);

                        double difference = opposibleColliderHitwall - entityColliderHitwall;

                        if(difference >= 0 && spaceLeft > difference) {
                            spaceLeft = difference;
                        }
                    }
                } else if(direction == Direction::NEGATIVE) { //Left
                    /**
                     * Als (entiteit x <= collidable x+w) && (check entiteit y-y+h in range collidable y-y+h)
                    **/

                    if(yStartEntity < yEndCollidable && yStartCollidable < yEndEntity) {
                        //Entities align on y-axiss
                        double opposibleColliderHitwall = transformComponent->xPos + ((transformComponent->xScale * collider->xScale) / 2);
                        double entityColliderHitwall = entityTransform->xPos - ((entityTransform->xScale * entityRectCollider->xScale) / 2);
                        
                        double difference = opposibleColliderHitwall - entityColliderHitwall;

                        if(difference <= 0 && spaceLeft < difference){
                            spaceLeft = difference;
                        }
                    }
                }
            } else if(axis == Axis::Y) {
                int xStartEntity = entityTransform->xPos - ((entityTransform->xScale * entityRectCollider->xScale) / 2);
                int xEndEntity = entityTransform->xPos + ((entityTransform->xScale * entityRectCollider->xScale) / 2);
                int xStartCollidable = transformComponent->xPos - ((transformComponent->xScale * collider->xScale) / 2);
                int xEndCollidable = transformComponent->xPos + ((transformComponent->xScale * collider->xScale) / 2);

                if(direction == Direction::POSITIVE) { //Down
                    /**
                     * Als (check entiteit x-x+w in range collidable x-x+w) && (entiteit y+h >= collidable y)
                     **/
                    if(xStartEntity < xEndCollidable && xStartCollidable < xEndEntity) {
                        double opposibleColliderHitwall = transformComponent->yPos - ((transformComponent->yScale * collider->yScale) / 2);
                        double entityColliderHitwall = entityTransform->yPos + ((entityTransform->yScale * entityRectCollider->yScale) / 2);
                        
                        double difference = opposibleColliderHitwall - entityColliderHitwall;

                        if(difference >= 0 && spaceLeft > difference){
                            spaceLeft = difference;
                        }
                    }
                } else if(direction == Direction::NEGATIVE) { //Up
                    /**
                     * Als (check entiteit x-x+w in range collidable x-x+w) && (entiteit y <= collidable y+h)
                     **/
                    if(xStartEntity < xEndCollidable && xStartCollidable < xEndEntity) {
                        //Entities align on x-axis
                        double opposibleColliderHitwall = transformComponent->yPos + ((transformComponent->yScale * collider->yScale) / 2);
                        double entityColliderHitwall = entityTransform->yPos - ((entityTransform->yScale * entityRectCollider->yScale) / 2);

                        double difference = opposibleColliderHitwall - entityColliderHitwall;

                        if(difference <= 0 && spaceLeft < difference){
                            spaceLeft = difference;
                        }
                    } 
                }
            }
        }
    }
    
    return spaceLeft;
}

#endif