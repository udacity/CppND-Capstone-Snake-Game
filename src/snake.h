#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <memory>
#include "SDL.h"
#include "settings.h"
namespace SnakeGame
{
  class Snake
  {
  public:
    enum class Direction
    {
      kUp,
      kDown,
      kLeft,
      kRight
    };

    Snake(int grid_width, int grid_height)
        : gridWidth_(grid_width),
          gridHeight_(grid_height),
          headX_(grid_width / 2),
          headY_(grid_height / 2) {}

    Snake() : Snake(SnakeGame::kGridWidth, SnakeGame::kGridHeight) {}
    ~Snake() = default;
    Snake(const Snake &other) = delete;
    Snake(Snake &&other) = delete;
    Snake &operator=(const Snake &other) = delete;
    Snake &operator=(Snake &&other) = delete;

    void Update();

    void GrowBody();
    bool SnakeCell(int x, int y);

    Direction direction_{Direction::kUp};

    float speed_{0.1F};
    unsigned int size_{1U};
    bool isAlive_{true};
    float headX_;
    float headY_;
//    std::vector<SDL_Point> body_;

    std::vector<std::unique_ptr<SDL_Point>>body_;

  private:
    void UpdateHead();
    void UpdateBody(std::unique_ptr<SDL_Point> current_cell, std::unique_ptr<SDL_Point> prev_cell);

    bool isGrowing_{false};
    int gridWidth_;
    int gridHeight_;
  };
}
#endif