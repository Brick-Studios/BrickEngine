#ifndef FILE_IMAGE_HPP
#define FILE_IMAGE_HPP

#include <memory>
#include <string>
#include <optional>

#include "SDL2/SDL.h"

#include "brickengine/rendering/renderable.hpp"

class Image
{
private:
    SDL_Surface* surface;
public:
    Image(const std::string path);
    ~Image();
};

#endif /* FILE_IMAGE_HPP */
