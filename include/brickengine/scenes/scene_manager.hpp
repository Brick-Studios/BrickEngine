#ifndef FILE_SCENE_MANAGER_HPP
#define FILE_SCENE_MANAGER_HPP

#include "brickengine/json_parser/json.hpp"

#include <string>

class SceneManager {
public:
    void createScene(std::string name) const;
private:
};

#endif // FILE_SCENE_MANAGER_HPP