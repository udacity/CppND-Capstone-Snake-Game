#ifndef ACTOR_H
#define ACTOR_H

#include <vector>
#include "SDL.h"

class Actor {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Actor(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        body_x(grid_width / 2),
        body_y(grid_height / 2) {}

  void Update();

  float speed{0.1f};
  Direction direction = Direction::kUp;
  float body_x;
  float body_y;
  bool alive{true};

 private:
  int grid_width;
  int grid_height;
};

#endif