#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <memory>
#include "SDL.h"
#include "settings.h"
namespace SnakeGame
{

struct SnakeColour {
    unsigned char red_;
    unsigned char green_;
    unsigned char blue_;
};
class Snake
{
public:


  Snake(int grid_width, int grid_height,bool isPlayerVirtual);

  Snake() : Snake(SnakeGame::kGridWidth, SnakeGame::kGridHeight,false) {}
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
  // default value is white - it will be used for human player
  SnakeColour colour_{ 0xFF, 0xFF, 0xFF};     

private:
  void UpdateHead();
  void UpdateBody(std::unique_ptr<SDL_Point> current_cell, std::unique_ptr<SDL_Point> prev_cell);

  bool isGrowing_{false};

};
}
#endif