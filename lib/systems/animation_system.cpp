#include "brickengine/systems/animation_system.hpp"
#include "brickengine/components/animation_component.hpp"
#include "brickengine/components/renderables/texture_component.hpp"

AnimationSystem::AnimationSystem(std::shared_ptr<EntityManager> entity_manager)
                : System(entity_manager) {}

void AnimationSystem::update(double deltatime){
    auto entities_with_animation = entityManager->getEntitiesByComponent<AnimationComponent>();

    for(auto& [entityId, animation] : entities_with_animation) {
        auto texture = entityManager->getComponent<TextureComponent>(entityId);

        if (animation) {
            animation->time += deltatime;
            if (animation->time >= animation->update_time){
                animation->seconds++;
                animation->time = 0;
            }
            animation->sprite = animation->seconds % animation->sprite_size;
            auto src = texture->getTexture()->getSrcRect();
            if (src) {
                src->x = abs(animation->sprite * src->w);
            }
        }
    }
}
