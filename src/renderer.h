#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <memory>
#include "SDL.h"

class Runner;
class Obstacle;

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t cols, const std::size_t rows);
  ~Renderer();

  void Render(Runner &runner, std::vector<std::unique_ptr<Obstacle> > &obstacles);
  void UpdateWindowTitle(const int score, const int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t cols;
  const std::size_t rows;
};

#endif