#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "shooter.h"
#include "EnemyShipManager.h"
#include "missile.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Shooter const &shooter, EnemyShipManager const &enemyShipManager);
  void RenderBlank();
  void UpdateWindowTitle(const std::string & windowTitle);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif
