#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };
  // default constructor
  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}

  // constructor: head only, define head position
  Snake(int grid_width, int grid_height, float head_x, float head_y, float speed)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(head_x),
        head_y(head_x),
        size(size),
        speed(speed) {}

  // constructor: given body size and head position 
  // TODO: change size from fixed to an abitrary number
  Snake(int grid_width, int grid_height, float head_x, float head_y, float speed, int size)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(head_x),
        head_y(head_y),
        size(size),
        speed(speed) {
          SDL_Point body_cell1{static_cast<int>(head_x), static_cast<int>(head_y-1)};
          SDL_Point body_cell2{static_cast<int>(head_x), static_cast<int>(head_y-2)};
          SDL_Point body_cell3{static_cast<int>(head_x), static_cast<int>(head_y-3)};
          SDL_Point body_cell4{static_cast<int>(head_x), static_cast<int>(head_y-4)};
          body.push_back(body_cell1);
          body.push_back(body_cell2);
          body.push_back(body_cell3);
          body.push_back(body_cell4);
        }

  void Update();

  void GrowBody();
  bool SnakeCell(int x, int y);

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1}; //size of the body+head
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false}; //if growing, don't erase tail
  int grid_width;
  int grid_height;
};

#endif