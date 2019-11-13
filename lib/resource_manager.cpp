#include "brickengine/resource_manager.hpp"
#include "SDL_image.h"
#include <iostream>

ResourceManager::ResourceManager(std::shared_ptr<Renderer> renderer){
    this->renderer = renderer;
}

std::shared_ptr<SDL_Texture> ResourceManager::getTexture(std::string path) {
    if (texture_pool.count(path) > 0) { // The texture atleast used to be created
        if (texture_pool.at(path).expired()) { // Create the texture, because it has been expired
            auto shared_texture = createTexture(path);
            std::weak_ptr<SDL_Texture> weak_texture = shared_texture;
            texture_pool.insert({ path, weak_texture });
            return shared_texture;
        } else { // The texture exists
            return texture_pool.at(path).lock();
        }
    } else { // Create the texture, because it was never created
        auto shared_texture = createTexture(path);
        std::weak_ptr<SDL_Texture> weak_texture = shared_texture;
        texture_pool.insert({ path, weak_texture });
        return shared_texture;
    }
}

std::shared_ptr<SDL_Texture> ResourceManager::createTexture(std::string path) const {
    SDL_Surface* surface = IMG_Load(path.c_str());

    if (surface == nullptr) {
        std::cout << "Failed to load surface " << path
            << " error : " << IMG_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* t = renderer.get()->createTextureFromSurface(surface);
    SDL_FreeSurface(surface);

    auto shared_ptr = std::shared_ptr<SDL_Texture>(t, SDL_DestroyTexture);
    return shared_ptr;
}