#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"

#include <iostream>

class Renderer
{
public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();
  Renderer(const Renderer &other) = delete;
  Renderer &operator=(const Renderer &other) = delete;
  Renderer(Renderer &&other) = delete;
  Renderer &operator=(Renderer &&other) = delete;

  void Render(Snake const snake, SDL_Point const &food);
  void UpdateWindowTitle(int score, int fps);

private:
  SDL_Window *sdlWindow_;
  SDL_Renderer *sdlRenderer_;

  const std::size_t screenWidth_;
  const std::size_t screenHeight_;
  const std::size_t gridWidth_;
  const std::size_t gridHeight_;
};

#endif