#include "brickengine/systems/displacement_system.hpp"
#include "brickengine/components/colliders/rectangle_collider_component.hpp"
#include "brickengine/components/physics_component.hpp"

DisplacementSystem::DisplacementSystem(std::shared_ptr<EntityManager> em, CollisionDetector2& cd)
    : System(em), collision_detector(cd) {}

void DisplacementSystem::update(double) {
    auto entities_with_collider = entityManager->getEntitiesByComponent<RectangleColliderComponent>();

    for (auto& [ entity_id, entity_collider ] : entities_with_collider) {
        auto entity_physics = entityManager->getComponent<PhysicsComponent>(entity_id);
        if (!entity_physics) continue;
        // We only displace entities that use Discrete collision detection - Collision Detector 2 ©
        if (entity_physics->collision_detection != CollisionDetectionType::Discrete) continue;
        // If the entity is standing was standing still, there is no use in going any further
        if (entity_physics->vx == 0 && entity_physics->vy == 0) continue;
        // If the collider is trigger, then the entity should not be displaced.
        if (entity_collider->is_trigger) continue;
        
        std::vector<DiscreteCollision> collisions = collision_detector.detectDiscreteCollision(entity_id);
        // No collisions? Just continue
        if (collisions.empty()) continue;

        auto [ entity_position, entity_scale ] = entityManager->getAbsoluteTransform(entity_id);

        for (DiscreteCollision& collision : collisions) {
            if (collision.opposite.is_trigger) continue;

            auto opposite_collider = entityManager->getComponent<RectangleColliderComponent>(collision.opposite.id);
            auto [ opposite_position, opposite_scale ] = entityManager->getAbsoluteTransform(collision.opposite.id);

            double entity_left = entity_position.x + ((entity_scale.x * entity_collider->x_scale) / 2);
            double entity_right = entity_position.x - ((entity_scale.x * entity_collider->x_scale) / 2);
            double entity_down = entity_position.y + ((entity_scale.y * entity_collider->y_scale) / 2);
            double entity_up = entity_position.y - ((entity_scale.y * entity_collider->y_scale) / 2);

            double opposite_left = opposite_position.x - ((opposite_scale.x * opposite_collider->x_scale) / 2);
            double opposite_right = opposite_position.x + ((opposite_scale.x * opposite_collider->x_scale) / 2);
            double opposite_down = opposite_position.y - ((opposite_scale.y * opposite_collider->y_scale) / 2);
            double opposite_up = opposite_position.y + ((opposite_scale.y * opposite_collider->y_scale) / 2);

            double time_x_collision = (entity_left - opposite_right) / - entity_physics->vx;
            double time_y_collision = (opposite_down - entity_up) / -entity_physics->vy;

            if (time_x_collision < time_y_collision) {
                // time_x_collision was faster
            } else {
                // time_y_collision was faster      
            }
        }

    }
}