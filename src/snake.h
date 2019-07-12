#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake() {}
  Snake(int grid_width, int grid_height);

  void Update();
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);
  void GrowBody(int quantity);
  bool SnakeCell(int x, int y);

  Direction last_dir = Direction::kUp;
  Direction dir = Direction::kUp;

  std::vector<SDL_Point> body;

  int growing = 0;
  float speed = 0.1f;
  int size = 1;
  bool alive = true;

  float head_x;
  float head_y;

  int grid_width;
  int grid_height;
};

#endif