#ifndef FILE_SCENE_HPP
#define FILE_SCENE_HPP

#include <optional>
#include <vector>
#include <memory>

#include "brickengine/components/component.hpp"
#include "enums/scene_layer.hpp"

template<typename State>
class Scene {
public:
    Scene(SceneLayer layer) : layer(layer) {}
    // Fils the entities
    virtual void prepare() = 0;
    virtual void start() = 0;
    virtual void leave() = 0;
    virtual State getSystemState() = 0;
    virtual std::string getTag() = 0;
    std::optional<std::unique_ptr<std::vector<std::vector<std::unique_ptr<Component>>>>> getEntityComponents() const {
        if (!entity_components)
            return std::nullopt;
        auto r = std::move(*entity_components);
        entity_components = std::nullopt;
        return r;
    }
    bool prepared() const {
        return entity_components.has_value();
    }
    SceneLayer getLayer() const {
        return layer;
    }
    virtual ~Scene() = default;
private:
    SceneLayer layer;
    // If entity_components are nullopt then the Scene has already been loaded or it has not been prepared yet.
    std::optional<std::unique_ptr<std::vector<std::vector<std::unique_ptr<Component>>>>> entity_components;
};

#endif // FILE_SCENE_HPP