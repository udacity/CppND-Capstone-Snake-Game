#include "renderer.h"
#include <iostream>
#include <string>
#include <algorithm>
namespace SnakeGame
{

  Renderer::Renderer(const std::size_t screen_width,
                     const std::size_t screen_height,
                     const std::size_t grid_width, const std::size_t grid_height)
      : width_(screen_width / (grid_width != 0U ? grid_width : 2U)),
        height_(screen_height / (grid_height != 0U ? grid_height : 2U)) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
      std::cerr << "SDL could not initialize.\n";
      std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create Window
    sdlWindow_ = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, screen_width,
                                  screen_height, SDL_WINDOW_SHOWN);

    if (nullptr == sdlWindow_)
    {
      std::cerr << "Window could not be created.\n";
      std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create renderer
    sdlRenderer_ = SDL_CreateRenderer(sdlWindow_, -1, SDL_RENDERER_ACCELERATED);
    if (nullptr == sdlRenderer_)
    {
      std::cerr << "Renderer could not be created.\n";
      std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }
  }

  Renderer::~Renderer()
  {
    SDL_DestroyWindow(sdlWindow_);
    SDL_Quit();
  }

  void Renderer::RenderFood(SDL_Point const &food) const {
        // Render food
    SDL_SetRenderDrawColor(sdlRenderer_, 0xFF, 0xCC, 0x00, 0xFF);
    SDL_Rect block{(food.x * width_),(food.y * height_),width_,height_};
    SDL_RenderFillRect(sdlRenderer_, &block);

  }

  void Renderer::RenderSnake(Snake * snake) const {
    // Render snake's body
    SDL_SetRenderDrawColor(sdlRenderer_, 0xFF, 0xFF, 0xFF, 0xFF);

    SDL_Rect block{( static_cast<int>(snake->headX_) * width_),(static_cast<int>(snake->headY_) * height_),width_,height_};

    auto updateBlock = [&](std::unique_ptr<SDL_Point> &point) {
      block.x = point->x * block.w;
      block.y = point->y * block.h;
      SDL_RenderFillRect(sdlRenderer_, &block);
    };

    std::for_each(snake->body_.begin(), snake->body_.end(), updateBlock);

    // Render snake's head
    block.x = static_cast<int>(snake->headX_) * block.w;
    block.y = static_cast<int>(snake->headY_) * block.h;
    if (snake->isAlive_) {
      SDL_SetRenderDrawColor(sdlRenderer_, 0x00, 0x7C, 0xFC, 0x00);
    } else {
      SDL_SetRenderDrawColor(sdlRenderer_, 0xFF, 0x00, 0x00, 0xFF);
    }
    SDL_RenderFillRect(sdlRenderer_, &block);       
  }

  void Renderer::RenderSnake(Snake & snake) const {
    // Render snake's body
    SDL_SetRenderDrawColor(sdlRenderer_, 0xFF, 0xFF, 0xFF, 0xFF);

    SDL_Rect block{( static_cast<int>(snake.headX_) * width_),(static_cast<int>(snake.headY_) * height_),width_,height_};

    auto updateBlock = [&](std::unique_ptr<SDL_Point> &point) {
      block.x = point->x * block.w;
      block.y = point->y * block.h;
      SDL_RenderFillRect(sdlRenderer_, &block);
    };

    std::for_each(snake.body_.begin(), snake.body_.end(), updateBlock);

    // Render snake's head
    block.x = static_cast<int>(snake.headX_) * block.w;
    block.y = static_cast<int>(snake.headY_) * block.h;
    if (snake.isAlive_) {
      SDL_SetRenderDrawColor(sdlRenderer_, 0x00, 0x7C, 0xFC, 0x00);
    } else {
      SDL_SetRenderDrawColor(sdlRenderer_, 0xFF, 0x00, 0x00, 0xFF);
    }
    SDL_RenderFillRect(sdlRenderer_, &block);    
  }

  void Renderer::Render(Snake  *snake, SDL_Point  &food)
  {
    // Clear screen
    SDL_SetRenderDrawColor(sdlRenderer_, 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(sdlRenderer_);

    RenderFood(food);

    RenderSnake(snake);

    // Update Screen
    SDL_RenderPresent(sdlRenderer_);
  }

  void Renderer::UpdateWindowTitle(int score, int fps)
  {
    std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
    SDL_SetWindowTitle(sdlWindow_, title.c_str());
  }
}