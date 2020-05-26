#ifndef ENEMY_H
#define ENEMY_H

#include "SDL.h"
#include <thread>
#include <mutex>

class Enemy {
 public:

   enum class Direction { kUp, kDown, kLeft, kRight };

   Enemy(SDL_Point body, Direction direction)
      : body_x(body.x),
        body_y(body.y), 
        direction(direction) {}
   ~Enemy();

    void Start(){enemyThread = std::thread(&Enemy::UpdatePosition, this);};
    void UpdatePosition();  
    SDL_Point GetEnemyPosition();
    Direction direction;

 private:
  std::thread enemyThread;
  float speed{0.1f};
  float body_x;
  float body_y;
};

#endif