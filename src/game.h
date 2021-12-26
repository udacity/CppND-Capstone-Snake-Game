#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "obstacle.h"
#include "runner.h"

typedef std::vector<std::unique_ptr<Obstacle> > ObstacleVector;
typedef std::vector<std::unique_ptr<Obstacle> >::iterator ObstacleItr;
class Game {
public:
  Game(std::size_t width, std::size_t height, std::size_t cols, std::size_t rows);
  void Run(std::size_t target_frame_duration);
  int Score() const;
  void ShiftRunner(int delta);

private:
  Renderer       renderer;
  Controller     controller;
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