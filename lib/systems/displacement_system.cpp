#include "brickengine/systems/displacement_system.hpp"
#include "brickengine/components/colliders/rectangle_collider_component.hpp"
#include "brickengine/components/physics_component.hpp"
#include <tuple>

DisplacementSystem::DisplacementSystem(CollisionDetector2& cd, std::shared_ptr<EntityManager> em)
    : System(em), collision_detector(cd) {}

void DisplacementSystem::update(double) {
    auto entities_with_collider = entityManager->getEntitiesByComponent<RectangleColliderComponent>();

    for (const auto& [ entity_id, entity_collider ] : entities_with_collider) {
        std::ignore = entity_collider;
        auto entity_physics = entityManager->getComponent<PhysicsComponent>(entity_id);
        if (!entity_physics) continue;
        // We only displace entities that use Discrete collision detection - Collision Detector 2 ©
        if (entity_physics->collision_detection != CollisionDetectionType::Discrete) continue;
        // If the entity is standing was standing still, there is no use in going any further
        if (entity_physics->vx == 0 && entity_physics->vy == 0) continue;
        if (!entity_collider->should_displace) continue;

        std::vector<DiscreteCollision> collisions = collision_detector.detectDiscreteCollision(entity_id);
        // No collisions? Just continue
        if (collisions.empty()) continue;

        auto entity_transform = entityManager->getComponent<TransformComponent>(entity_id);

        for (const DiscreteCollision& collision : collisions) {
            if (collision.is_trigger) continue;
            auto opposite_collider = entityManager->getComponent<RectangleColliderComponent>(collision.opposite_id);
            if (!opposite_collider->should_displace) continue;
            entity_transform->x_pos += collision.delta.x;
            entity_transform->y_pos += collision.delta.y;

            if (collision.delta.x != 0)
                entity_physics->vx = 0;
            if (collision.delta.y != 0)
                entity_physics->vy = 0;
        }
    }
}
