#include <string>
#include <memory>
#include <iostream>

#include "image.hpp"

Image::Image(const std::string path)
{
    surface = std::make_unique<SDL_Surface>(SDL_LoadBMP(path.c_str()));
    if(surface == NULL )
    {
        std::cout << "Opening an image asset failed!\nImage: " << path << " SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
}
Image::~Image()
{
}