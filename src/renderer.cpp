#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t cols, const std::size_t rows)
    : screen_width(screen_width),
      screen_height(screen_height),
      cols(cols),
      rows(rows)
{
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Runner Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer()
{
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Runner &runner, ObstacleVector &obstacles)
{
  SDL_Rect block;
  block.w = screen_width / cols;
  block.h = screen_height / rows;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 241, 222, 222, 255); // #F1DEDE
  SDL_RenderClear(sdl_renderer);

  // Render runner
  RBGA &colour = runner.getColour();
  block.x = static_cast<int>(runner.getX()) * block.w;
  block.y = static_cast<int>(runner.getY()) * block.h;
  SDL_SetRenderDrawColor(sdl_renderer, colour.r, colour.b, colour.g, colour.a);
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render obstacles
  for (ObstacleItr &ob : obstacles)
  {
    RBGA &colour = ob->getColour();
    block.x = static_cast<int>(ob->getX()) * block.w;
    block.y = static_cast<int>(ob->getY()) * block.h;
    SDL_SetRenderDrawColor(sdl_renderer, colour.r, colour.b, colour.g, colour.a);
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps)
{
  std::string title{"Runner Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
