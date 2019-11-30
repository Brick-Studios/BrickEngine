#include "brickengine/systems/displacement_system.hpp"
#include "brickengine/components/colliders/rectangle_collider_component.hpp"
#include "brickengine/components/physics_component.hpp"

DisplacementSystem::DisplacementSystem(std::unordered_map<std::string, std::set<std::string>> is_trigger_tag_exceptions, CollisionDetector2& cd, std::shared_ptr<EntityManager> em)
    : System(em), collision_detector(cd), is_trigger_tag_exceptions(is_trigger_tag_exceptions) {}

bool DisplacementSystem::findDisplacementException(std::set<std::string> tags_1, std::set<std::string> tags_2) {
    for (const std::string& tag_1 : tags_1) {
        if (is_trigger_tag_exceptions.count(tag_1)) {
            for (const std::string& tag_2 : tags_2) {
                if (is_trigger_tag_exceptions.at(tag_1).count(tag_2)) {
                    return true;
                }
            }
        }
    }
    for (const std::string& tag_2 : tags_2) {
        if (is_trigger_tag_exceptions.count(tag_2)) {
            for (const std::string& tag_1 : tags_1) {
                if (is_trigger_tag_exceptions.at(tag_2).count(tag_1)) {
                    return true;
                }
            }
        }
    }
    return false;
}

void DisplacementSystem::update(double) {
    auto entities_with_collider = entityManager->getEntitiesByComponent<RectangleColliderComponent>();

    for (const auto& [ entity_id, entity_collider ] : entities_with_collider) {
        auto entity_physics = entityManager->getComponent<PhysicsComponent>(entity_id);
        if (!entity_physics) continue;
        // We only displace entities that use Discrete collision detection - Collision Detector 2 ©
        if (entity_physics->collision_detection != CollisionDetectionType::Discrete) continue;
        // If the entity is standing was standing still, there is no use in going any further
        if (entity_physics->vx == 0 && entity_physics->vy == 0) continue;
        
        std::vector<DiscreteCollision> collisions = collision_detector.detectDiscreteCollision(entity_id);
        // No collisions? Just continue
        if (collisions.empty()) continue;

        auto entity_transform = entityManager->getComponent<TransformComponent>(entity_id);

        for (const DiscreteCollision& collision : collisions) {
            if (collision.entity.is_trigger || collision.opposite.is_trigger) {
                // If there are no is_trigger_exceptions for these colliding entities,
                // just continue, because is trigger needs to go through everything except
                // some things
                if (!findDisplacementException(entityManager->getTags(collision.entity.id),
                                              entityManager->getTags(collision.opposite.id)))
                    continue;
            }

            entity_transform->x_pos += collision.delta.x;
            entity_transform->y_pos += collision.delta.y;

            if (collision.delta.x != 0)
                entity_physics->vx = 0;
            if (collision.delta.y != 0)
                entity_physics->vy = 0;
        }
    }
}