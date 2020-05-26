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

  bool ActorCell(int x, int y);

  SDL_Point GetActorPosition();
  bool IsAlive();
  void SetAlive(bool alive) {alive = alive;}
  float speed{0.1f};

  
 private:
  int grid_width;
  int grid_height;
  float body_x;
  float body_y;
  bool alive{true};
  void UpdatePosition();
  Direction direction = Direction::kUp;
};

#endif