#ifndef FILE_SCENE_MANAGER_HPP
#define FILE_SCENE_MANAGER_HPP

#include <vector>
#include <complex>
#include <memory>
#include <unordered_map>
#include <functional>

#include "brickengine/components/component.hpp"
#include "brickengine/systems/system.hpp"
#include "brickengine/scenes/scene.hpp"
#include "brickengine/scenes/exceptions/another_scene_active.hpp"
#include "brickengine/scenes/exceptions/no_scene_active.hpp"
#include "brickengine/scenes/enums/scene_layer.hpp"
#include "brickengine/game_state_manager.hpp"

template<typename State>
class SceneManager {
public:
    SceneManager(EntityManager& em, GameStateManager<State>& gsm) : entity_manager(em), game_state_manager(gsm) {}
    void loadScene(std::unique_ptr<Scene<State>> scene) {
        if (scenes.count(scene->getLayer()))
            throw AnotherSceneActiveException();
        Scene<State>& scene_ref = *scene;
        // We need to insert the scene asap, because the entity manager will try to fetch the current scene tag when creating new entities
        scenes.insert({scene->getLayer(), std::move(scene)});

        if (!scene_ref.prepared()) {
            std::cout << "I am preparing 🧒" << std::endl;
            scene_ref.prepare();
            
        }
        auto entity_comps = scene_ref.getEntityComponents();
        if (entity_comps) {
            for (auto& entity_comps : *entity_comps) {
                entity_manager.createEntity(std::move(entity_comps), std::nullopt, scene_ref.getTag());
            }
        }
        scene_ref.start();
        game_state_manager.setState(scene_ref.getSystemState());
    }
    template <typename T, typename... Args, typename = std::enable_if_t<std::is_base_of_v<Scene<State>, T>>>
    void createScene(Args &&... args) {
        auto scene = std::make_unique<T>(std::forward<Args>(args)...);
        loadScene(std::move(scene));
    }
    void destroyScene(SceneLayer layer) {
        if (!scenes.count(layer)) return;

        scenes.at(layer)->leave();
        entity_manager.removeEntitiesWithTag(scenes.at(layer)->getTag());
        scenes.erase(layer);
    }
    void destroyAllScenes() {
        for (auto& [ layer, scene ] : scenes) {
            scene->leave();
            entity_manager.removeEntitiesWithTag(scene->getTag());
        }
        scenes.clear();
    }
    template <typename T, typename = std::enable_if_t<std::is_base_of_v<Scene<State>, T>>>
    bool isSceneActive() {
        if (scenes.count(T::getLayerStatic()))
            return scenes.at(T::getLayerStatic())->getTag() == T::getTagStatic();
        return false;
    }
    std::string getLayerTag(SceneLayer layer) const {
        return scenes.at(layer)->getTag();
    }
    std::function<std::optional<std::string>()> createGetPrimaryTagFunction() const {
        return [sm = this]() -> std::optional<std::string> {
            if (sm->scenes.count(SceneLayer::Primary))
                return sm->scenes.at(SceneLayer::Primary)->getTag();
            else
                return std::nullopt;
        };
    }
private:
    EntityManager& entity_manager;
    GameStateManager<State>& game_state_manager;

    std::unordered_map<SceneLayer, std::unique_ptr<Scene<State>>> scenes;
};

#endif // FILE_SCENE_MANAGER_HPP