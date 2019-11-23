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
    Scene() = default;
    // Fils the entities
    virtual void prepare() = 0;
    virtual void start() = 0;
    virtual void leave() = 0;
    virtual State getSystemState() const = 0;
    virtual std::string getTag() const = 0;
    virtual SceneLayer getLayer() const = 0;
    std::unique_ptr<std::vector<std::unique_ptr<std::vector<std::unique_ptr<Component>>>>> getEntityComponents() {
        return std::move(entity_components);
    }
    bool prepared() const {
        return entity_components != nullptr;
    }
    virtual ~Scene() = default;
protected:
    // If entity_components is nullptr then the Scene has already been loaded or it has not been prepared yet.
    std::unique_ptr<std::vector<std::unique_ptr<std::vector<std::unique_ptr<Component>>>>> entity_components;
};

#endif // FILE_SCENE_HPP