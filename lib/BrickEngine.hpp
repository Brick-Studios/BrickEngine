#include <optional>

#include "SDL2/SDL.h"
#include "SDL2/SDL_net.h"

typedef struct SDL_Window SDL_Window;

class BrickEngine {
public:
    static void OpenWindow(const char* title,
                             int         x,
                             int         y,
                             int         w,
                             int         h) {
    }

private:
    std::optional<SDL_Window> sdl_window;
};
