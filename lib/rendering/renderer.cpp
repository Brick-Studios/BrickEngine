#include <memory>
#include "SDL2/SDL.h"
#include "brickengine/rendering/renderer.hpp"

Renderer::Renderer(std::unique_ptr<const SDL_Renderer> r){
    
}

// void DrawScreen() {
//     //Loads individual image as texture
//     SDL_Texture* loadTexture( std::string path );

//     //The window we'll be rendering to
//     SDL_Window* gWindow = NULL;

//     //The window renderer
//     SDL_Renderer* gRenderer = NULL;

//     //Current displayed texture
//     SDL_Texture* gTexture = NULL;
// }