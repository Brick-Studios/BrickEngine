#ifndef FILE_SCENE_IMPL_HPP
#define FILE_SCENE_IMPL_HPP

#include "brickengine/scenes/scene.hpp"

template<typename SceneType, typename State>
class SceneImpl : public Scene<State> {
public:
    virtual std::string getTag() const {
        return SceneType::getTagStatic();
    }
    virtual SceneLayer getLayer() const {
        return SceneType::getLayerStatic();
    }
};

#endif // FILE_SCENE_IMPL_HPP