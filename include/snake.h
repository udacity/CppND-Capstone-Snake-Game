#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <queue>

#include "SDL.h"
#include "grid_route_planner.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };
  enum class Mode { Manual, Autonomous };

  Snake(int grid_width, int grid_height, int dx, int dy)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2 + dx),
        head_y(grid_height / 2 + dy) {}

  void Update();
  void GrowBody();
  bool SnakeCell(int x, int y);

  void SetMode(Mode m) { mode = m; };
  Mode GetMode() const { return mode; };
  bool IsAutonomous() { return mode == Mode::Autonomous ? true : false ; };

  void SetPlannedPath(const std::vector<Node*> &path) {
    planned_path.clear();
    for (auto* p : path) planned_path.push_back(p);
  }
  void ClearPlannedPath() { planned_path.clear(); }
  bool HasPlannedPath() const { return !planned_path.empty(); }

  Direction direction = Direction::kUp;
  Mode mode{Mode::Autonomous};

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;
  bool replan_requested{false};

 private:
  void UpdateHeadManual();
  void UpdateHeadAutonomous();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);
  static Direction Opposite(Direction d) {
    switch (d) {
      case Direction::kUp:    return Direction::kDown;
      case Direction::kDown:  return Direction::kUp;
      case Direction::kLeft:  return Direction::kRight;
      case Direction::kRight: return Direction::kLeft;
    }
    return d;
  }

  bool growing{false};
  int grid_width;
  int grid_height;

  std::deque<Node*> planned_path;
};

#endif