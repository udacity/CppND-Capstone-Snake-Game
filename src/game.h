#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>
#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "obstacle.h"
#include "runner.h"

class Game {
public:
  Game(std::size_t cols, std::size_t rows);
  void Run(const Controller &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int  GetScore() const;
  void ShiftRunner(int delta);

private:
  const std::size_t cols, rows;
  Runner         runner;
  ObstacleVector obstacles;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_x;
  std::uniform_int_distribution<int> random_type;

  void GenerateObstacles();
  void CleanObstacles();
  void Update();
};

#endif