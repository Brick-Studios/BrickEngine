#include "brickengine/systems/rendering_system.hpp"
#include "brickengine/components/transform_component.hpp"
#include "brickengine/components/renderables/texture_component.hpp"
#include <iostream>

RenderingSystem::RenderingSystem(std::shared_ptr<EntityManager> entityManager, Renderer& renderer)
                : System(entityManager), renderer(renderer) {}

void RenderingSystem::update(double){
    auto entitiesWithTexture = entityManager->getEntitiesByComponent<TextureComponent>();

    for(auto& [entityId, texture] : *entitiesWithTexture) {
        TransformComponent* transform = entityManager->getComponent<TransformComponent>(entityId);

        auto dst = texture->getTexture()->getDstRect();
        int x = transform->getXPos() - (transform->getXScale() / 2);
        int y = transform->getYPos() - (transform->getYScale() / 2);
        dst->x = x;
        dst->y = y;
        dst->w = transform->getXScale();
        dst->h = transform->getYScale();

        renderer.queueRenderable(texture->getTexture());
    }
}