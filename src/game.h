#ifndef GAME_H
#define GAME_H

#include <random>
#include <thread>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "bad_food.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  ~Game();
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  Snake snake;
  SDL_Point food;
  BadFood badFood;
  std::thread badFoodTimer;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  float speed_increment = 0.01;

  void PlaceFood();
  void PlaceBadFood();
  void Update();
};

#endif