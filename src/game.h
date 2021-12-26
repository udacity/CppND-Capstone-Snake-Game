#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>
#include "SDL.h"
#include "runner.h"
#include "obstacle.h"
#include "utility.h"

class Controller;
class Renderer;
class Game
{
public:
  Game(std::size_t cols, std::size_t rows);
  void Run(const Controller &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int  GetScore() const;
  void ShiftRunner(int delta);

private:
  const std::size_t cols, rows;
  Runner         runner;

  Random<int> random_x;
  Random<int> random_type;
  Random<int> random_time;
  
  ObstacleVector obstacles;
  TimeChecker    obTimer;

  void GenerateObstacles();
  void CleanObstacles();
  void Update();
};

#endif