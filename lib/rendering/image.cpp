#include <string>
#include <memory>
#include <iostream>

#include "brickengine/rendering/renderables/image.hpp"

Image::Image(const std::string path)
{
    surface = SDL_LoadBMP(path.c_str());
    if(surface == nullptr)
    {
        std::cout << "Opening an image asset failed!\nImage: " << path << " SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
}
Image::~Image()
{
}