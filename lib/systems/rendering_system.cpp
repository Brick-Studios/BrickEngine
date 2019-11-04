#include "brickengine/systems/rendering_system.hpp"
#include "brickengine/components/transform_component.hpp"
#include "brickengine/components/renderables/texture_component.hpp"
#include <iostream>

RenderingSystem::RenderingSystem(std::shared_ptr<EntityManager> entityManager, Renderer& renderer)
                : System(entityManager), renderer(renderer) {}

void RenderingSystem::update(double){
    auto entitiesWithTexture = entityManager->getEntitiesByComponent<TextureComponent>();

    for(auto& [entityId, texture] : *entitiesWithTexture) {
        auto transform = entityManager->getComponent<TransformComponent>(entityId);

        auto dst = texture->getTexture()->getDstRect();
        auto [ position, scale ] = entityManager->getAbsoluteTransform(entityId);
        dst->x = position.x - (scale.x / 2);
        dst->y = position.y - (scale.y / 2);
        dst->w = scale.x;
        dst->h = scale.y;        

        texture->getTexture()->setFlip(SDL_FLIP_NONE);
        SDL_RendererFlip flip = SDL_FLIP_NONE;

        if (transform->xDirection == Direction::POSITIVE && transform->yDirection == Direction::POSITIVE) {
            flip = static_cast<SDL_RendererFlip>(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
        } else if (transform->xDirection == Direction::POSITIVE) {
            flip = SDL_FLIP_HORIZONTAL;
        } else if (transform->yDirection == Direction::POSITIVE) {
            flip = SDL_FLIP_VERTICAL;
        }

        if (transform->xDirection == Direction::POSITIVE) {
            texture->getTexture()->setFlip(SDL_FLIP_NONE);
        } else {
            texture->getTexture()->setFlip(SDL_FLIP_HORIZONTAL);
        }

        renderer.queueRenderable(texture->getTexture());
    }
}