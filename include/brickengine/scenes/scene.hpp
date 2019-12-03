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
    Scene() : prepared(false) {}
    // Fills the entities
    void prepare() {
        performPrepare();
        prepared = true;
    }
    virtual void start() = 0;
    virtual void leave() = 0;
    virtual State getSystemState() const = 0;
    virtual std::string getTag() const = 0;
    virtual SceneLayer getLayer() const = 0;
    std::unique_ptr<std::vector<std::unique_ptr<std::vector<std::unique_ptr<Component>>>>> getEntityComponents() {
        prepared = false;
        return std::move(entity_components);
    }
    bool isPrepared() const {
        return prepared;
    }
    virtual ~Scene() = default;
protected:
    virtual void performPrepare() = 0;
    // This can be nullptr as not all scenes actually use entity_components
    std::unique_ptr<std::vector<std::unique_ptr<std::vector<std::unique_ptr<Component>>>>> entity_components;
    bool prepared;
};

#endif // FILE_SCENE_HPP
