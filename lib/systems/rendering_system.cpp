#include "brickengine/systems/rendering_system.hpp"
#include "brickengine/components/transform_component.hpp"
#include "brickengine/components/physics_component.hpp"
#include "brickengine/components/renderables/texture_component.hpp"
#include <iostream>

RenderingSystem::RenderingSystem(std::shared_ptr<EntityManager> entityManager, Renderer& renderer)
                : System(entityManager), renderer(renderer) {}

void RenderingSystem::update(double){
    auto entitiesWithTexture = entityManager->getEntitiesByComponent<TextureComponent>();

    for(auto& [entityId, texture] : *entitiesWithTexture) {
        auto transform = entityManager->getComponent<TransformComponent>(entityId);

        auto dst = texture->getTexture()->getDstRect();
        int x = transform->xPos - (transform->xScale / 2);
        int y = transform->yPos - (transform->yScale / 2);
        dst->x = x;
        dst->y = y;
        dst->w = transform->xScale;
        dst->h = transform->yScale;

        auto physics = entityManager->getComponent<PhysicsComponent>(entityId);
        if (physics) {
            if (physics->vx < 0) {
                texture->getTexture()->setFlip(SDL_FLIP_HORIZONTAL);
            } else if (physics->vx > 0) {
                texture->getTexture()->setFlip(SDL_FLIP_NONE);
            }
        }

        renderer.queueRenderable(texture->getTexture());
    }
}