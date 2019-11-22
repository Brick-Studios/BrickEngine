#ifndef FILE_SCENE_IMPL_HPP
#define FILE_SCENE_IMPL_HPP

#include "brickengine/scenes/scene.hpp"

template<typename SceneType, typename State, typename Factory>
class SceneImpl : Scene<State, Factory> {
public:
    virtual std::string getTag() {
        SceneType::getTagStatic();
    }
};

#endif // FILE_SCENE_IMPL_HPP