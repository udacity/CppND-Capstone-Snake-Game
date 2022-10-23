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


    Snake(int grid_width, int grid_height);

    Snake() : Snake(SnakeGame::kGridWidth, SnakeGame::kGridHeight) {}
    ~Snake() = default;
    Snake(const Snake &other) = delete;
    Snake(Snake &&other) = delete;
    Snake &operator=(const Snake &other) = delete;
    Snake &operator=(Snake &&other) = delete;

    void Update();

    void GrowBody();
    bool SnakeCell(int x, int y);

    void ChangeDirection(const Direction input, const Direction opposite); 
    Direction direction_{Direction::kUp};

    float speed_{0.1F};
    unsigned int size_{1U};
    bool isAlive_{true};
    float headX_{0.f};
    float headY_{0.f};
    int gridWidth_;
    int gridHeight_;    

    std::vector<std::unique_ptr<SDL_Point>>body_;

  private:
    void UpdateHead();
    void UpdateBody(std::unique_ptr<SDL_Point> current_cell, std::unique_ptr<SDL_Point> prev_cell);

    bool isGrowing_{false};

  };
}
#endif