#ifndef FILE_SCENE_MANAGER_HPP
#define FILE_SCENE_MANAGER_HPP

#include <vector>
#include <complex>
#include <memory>
#include <unordered_map>

#include "brickengine/components/component.hpp"
#include "brickengine/systems/system.hpp"
#include "brickengine/scenes/scene.hpp"

template<typename State>
class SceneManager {
public:
    SceneManager(EntityManager& em) : entity_manager(em) {}
    void loadScene(Scene<State>& scene) {
        if (!scene.prepared())
            scene.prepare();
        for (auto& entity_comps : scene.getEntityComponents()) {
            entity_manager.createEntity(std::move(entity_comps));
        }
        scene.start();
        // insert all the new entities.
    }
    template <typename T, typename = std::enable_if_t<std::is_base_of_v<Scene, T>>, typename... Args>
    void loadScene(Args &&... args) {
        T scene { std::forward<Args>(args)... };
        scene.prepare();
        loadScene(scene);
        scene.start();
    }
    template <typename T, typename = std::enable_if_t<std::is_base_of_v<Scene, T>>>
    void destroyScene() {
        std::string tag = T::getTagStatic();
        entity_manager.removeEntitiesWithTag(tag);
        active_scene_tags.erase(tag);
    }
    void destroyAllScenes() {
        for (std::string& tag : active_scene_tags) {
            entity_manager.removeEntitiesWithTag(tag);
        }
        active_scene_tags.clear();
    }
    template <typename T, typename = std::enable_if_t<std::is_base_of_v<Scene, T>>>
    bool isSceneActive() {
        std::string tag = T::getTagStatic();
        return active_scene_tags.count(tag);
    }
private:
    EntityManager& entity_manager;

    std::set<std::string> active_scene_tags;
};

#endif // FILE_SCENE_MANAGER_HPP