#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "runner.h"
#include "obstacle.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t cols, const std::size_t rows);
  ~Renderer();

  void Render(Runner &runner, std::vector<Obstacle> &obstacles);
  void UpdateWindowTitle(int score, int fps);

  std::size_t ScreenWidth() { return screen_width; }
  std::size_t ScreenHeight() { return screen_height; }
  std::size_t Cols() { return cols; }
  std::size_t Rows() { return rows; }
  std::size_t ObjectWidth() { return screen_width / cols; }
  std::size_t ObjectHeight() { return screen_height / rows; }

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t cols;
  const std::size_t rows;
};

#endif