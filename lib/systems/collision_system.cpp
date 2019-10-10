#ifndef FILE_COLLISION_SYSTEM_CPP
#define FILE_COLLISION_SYSTEM_CPP

#include <limits>

#include "brickengine/systems/collision_system.hpp"
#include "brickengine/enum/axis.hpp"
#include "brickengine/enum/direction.hpp"

#include "brickengine/components/collision/collision_component.hpp"
#include "brickengine/components/collision/square_collision_component.hpp"

CollisionSystem::CollisionSystem(EntityManager* entityManager) : entityManager(entityManager) {}

double CollisionSystem::canMove(int entity, Axis axis, Direction direction) {
    //We only support squares.
    auto entityRectCollider = entityManager->getComponent<SquareCollisionComponent>(entity);
    auto collidableEntities = entityManager->getEntitiesByComponent<SquareCollisionComponent>();

    double spaceLeft = std::numeric_limits<double>::infinity(); //Distance to closest object
    for(auto& oppositeCollider : *collidableEntities) {
        int zStartEntity = entityRectCollider->z;
        int zEndEntity = entityRectCollider->z + entityRectCollider->vz;
        int zStartCollidable = oppositeCollider->component->z;
        int zEndCollidable = oppositeCollider->component->z + oppositeCollider->component->vz;

        if(oppositeCollider->id != entity && (zStartEntity <= zEndCollidable && zStartCollidable <= zEndEntity)) {
            if(axis == Axis::X) {
                double yStartEntity = entityRectCollider->y;
                double yEndEntity = entityRectCollider->y + entityRectCollider->h;
                double yStartCollidable = oppositeCollider->component->y;
                double yEndCollidable = oppositeCollider->component->y + oppositeCollider->component->h;
                
                if(direction == Direction::POSITIVE) { //Right
                    /**
                     * Als (entiteit x+w >= collidable x) && (check entiteit y-y+h in range collidable y-y+h)
                     **/

                    if(yStartEntity <= yEndCollidable && yStartCollidable <= yEndEntity) {
                        //Entities align on y-axis
                        double opposibleColliderHitwall = oppositeCollider->component->x;
                        double entityColliderHitwall = entityRectCollider->x + entityRectCollider->w;

                        double difference = opposibleColliderHitwall - entityColliderHitwall;

                        if(spaceLeft > difference) {
                            spaceLeft = difference;
                        }
                    }
                } else if(direction == Direction::NEGATIVE) { //Left
                    /**
                     * Als (entiteit x <= collidable x+w) && (check entiteit y-y+h in range collidable y-y+h)
                    **/

                    if(yStartEntity <= yEndCollidable && yStartCollidable <= yEndEntity) {
                        //Entities align on y-axis
                        double opposibleColliderHitwall = oppositeCollider->component->x  + oppositeCollider->component->w;
                        double entityColliderHitwall = entityRectCollider->x;

                        double difference =  entityColliderHitwall - opposibleColliderHitwall;

                        if(spaceLeft > difference) {
                            spaceLeft = difference;
                        }
                    }
                }
            } else if(axis == Axis::Y) {
                double xStartEntity = entityRectCollider->x;
                double xEndEntity = entityRectCollider->x + entityRectCollider->w;
                double xStartCollidable = oppositeCollider->component->x;
                double xEndCollidable = oppositeCollider->component->x + oppositeCollider->component->w;

                if(direction == Direction::POSITIVE) { //Down
                    /**
                     * Als (check entiteit x-x+w in range collidable x-x+w) && (entiteit y+h >= collidable y)
                     **/

                    if(xStartEntity <= xEndCollidable && xStartCollidable <= xEndEntity) {
                        //Entities align on x-axis
                        double opposibleColliderHitwall = oppositeCollider->component->y;
                        double entityColliderHitwall = entityRectCollider->y + entityRectCollider->h;

                        double difference =  opposibleColliderHitwall - entityColliderHitwall;

                        if(spaceLeft > difference) {
                            spaceLeft = difference;
                        }
                    }
                } else if(direction == Direction::NEGATIVE) { //Up
                    /**
                     * Als (check entiteit x-x+w in range collidable x-x+w) && (entiteit y <= collidable y+h)
                     **/

                    if(xStartEntity <= xEndCollidable && xStartCollidable <= xEndEntity) {
                        //Entities align on x-axis
                        double opposibleColliderHitwall = oppositeCollider->component->y + oppositeCollider->component->h;
                        double entityColliderHitwall = entityRectCollider->y;

                        double difference =  entityColliderHitwall - opposibleColliderHitwall;

                        if(spaceLeft > difference) {
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