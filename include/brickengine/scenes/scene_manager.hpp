#ifndef FILE_SCENE_MANAGER_HPP
#define FILE_SCENE_MANAGER_HPP

#include <vector>
#include <complex>
#include <memory>
#include <unordered_map>

#include "brickengine/components/component.hpp"
#include "brickengine/systems/system.hpp"
#include "brickengine/scenes/scene.hpp"
#include "brickengine/scenes/exceptions/another_scene_active.hpp"
#include "brickengine/scenes/exceptions/no_scene_active.hpp"
#include "brickengine/scenes/enums/scene_layer.hpp"

template<typename State>
class SceneManager {
public:
    SceneManager(EntityManager& em) : entity_manager(em) {}
    void loadScene(std::unique_ptr<Scene<State>> scene) {
        if (scenes.count(scene->getLayer()))
            throw AnotherSceneActiveException();

        if (!scene->prepared())
            scene->prepare();
        for (auto& entity_comps : scene->getEntityComponents()) {
            int id = entity_manager.createEntity(std::move(entity_comps));
            entity_manager.setTag(id, scene.getTag());
        }
        scene->start();
        scenes.insert({scene->getLayer(), std::move(scene)});
    }
    template <typename T, typename = std::enable_if_t<std::is_base_of_v<Scene<State>, T>>, typename... Args>
    void createScene(Args &&... args) {
        auto scene = std::make_unique<T>(std::forward<Args>(args)...);
        loadScene(std::move(scene));
    }
    void destroyScene(SceneLayer layer) {
        if (scenes.count(layer)) {
            scenes.at(layer)->leave();
            entity_manager.removeEntitiesWithTag(scenes.at(layer)->getTag());
            scenes.erase(layer);
        } else {
            throw NoSceneActiveException();
        }
    }
    void destroyAllScenes() {
        for (auto& [ layer, scene ] : scenes) {
            scene->leave();
            entity_manager.removeEntitiesWithTag(scene->getTag());
        }
        scenes.clear();
    }
    template <typename T, typename = std::enable_if_t<std::is_base_of_v<Scene<State>, T>>>
    bool isSceneActive(SceneLayer layer) {
        std::string tag = T::getTagStatic();
        return scenes.count(layer);
    }
private:
    EntityManager& entity_manager;

    std::unordered_map<SceneLayer, std::unique_ptr<Scene<State>>> scenes;
};

#endif // FILE_SCENE_MANAGER_HPP