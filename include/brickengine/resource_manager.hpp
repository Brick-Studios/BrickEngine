#ifndef FILE_RESOURCE_MANAGER_HPP
#define FILE_RESOURCE_MANAGER_HPP

#include <memory>
#include <unordered_map>
#include <string>
#include "SDL2/SDL.h"
#include "brickengine/rendering/renderer.hpp"

class ResourceManager {
public:
    ResourceManager(std::shared_ptr<Renderer> renderer);
    std::shared_ptr<SDL_Texture> getTexture(std::string path);
private:
    std::shared_ptr<SDL_Texture> createTexture(std::string path) const;
    std::unordered_map<std::string, std::weak_ptr<SDL_Texture>> texture_pool;

    std::shared_ptr<Renderer> renderer;
};

#endif /* FILE_RESOURCE_MANAGER_HPP */