#ifndef ENEMY_H
#define ENEMY_H

#include "SDL.h"
#include <thread>
#include <mutex>

class Enemy {
 public:

   enum class Direction { kUp, kDown, kLeft, kRight };

   Enemy(SDL_Point body, Direction direction, int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        body_x(body.x),
        body_y(body.y), 
        direction(direction) {}
   ~Enemy();

    void Start(){enemyThread = std::thread(&Enemy::UpdatePosition, this);};
    void UpdatePosition();  
    SDL_Point GetEnemyPosition();
    Direction direction;
    std::mutex mtx;
    float body_x;
    float body_y;

 private:
  int grid_width;
  int grid_height;
  std::thread enemyThread;
  float speed{0.1f};
};

#endif