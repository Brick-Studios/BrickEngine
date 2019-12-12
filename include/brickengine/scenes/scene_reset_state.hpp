#ifndef FILE_SCENE_RESET_STATE_HPP
#define FILE_SCENE_RESET_STATE_HPP

struct SceneResetState{
public:
    SceneResetState(bool reset_on_start, bool reset_on_end) : reset_on_start(reset_on_start), reset_on_end(reset_on_end) {}
    bool reset_on_start;
    bool reset_on_end;
};

#endif // FILE_SCENE_RESET_STATE_HPP