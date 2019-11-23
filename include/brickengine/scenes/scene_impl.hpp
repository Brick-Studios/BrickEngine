#ifndef FILE_SCENE_IMPL_HPP
#define FILE_SCENE_IMPL_HPP

#include "brickengine/scenes/scene.hpp"

template<typename SceneType, typename State>
class SceneImpl : Scene<State> {
public:
    SceneImpl(SceneLayer layer) : Scene<State>(layer) {}
    virtual std::string getTag() {
        return SceneType::getTagStatic();
    }
};

#endif // FILE_SCENE_IMPL_HPP