#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "snake.h"
#include "SDL.h"

class Renderer {

  public:

    Renderer(const std::size_t screen_width, const std::size_t screen_height, const std::size_t grid_width, const std::size_t grid_height);
    ~Renderer();
    
    void Render(Snake snake, SDL_Point &food);
    void UpdateWindowTitle(int score, int fps);

    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;

    const std::size_t screen_width;
    const std::size_t screen_height;
    const std::size_t grid_width;
    const std::size_t grid_height;
};

#endif