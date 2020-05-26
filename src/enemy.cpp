#include "enemy.h"
#include <iostream>

// destructor definition
Enemy::~Enemy(){
    enemyThread.join();
}

// move enemy back and forth
void Enemy::UpdatePosition(){
    std::unique_lock<std::mutex> lck(mtx);
    
    switch (direction) 
    {
    case Direction::kUp:
      body_y -= speed;
      break;

    case Direction::kDown:
      body_y += speed;
      break;

    case Direction::kLeft:
      body_x -= speed;
      break;

    case Direction::kRight:
      body_x += speed;
      break;
    }
    // Wrap the Actor around to the beginning if going off of the screen.
    body_x = fmod(body_x + grid_width, grid_width);
    body_y = fmod(body_y + grid_height, grid_height);

    lck.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

SDL_Point GetEnemyPosition(){
  SDL_Point position;
  position.x = static_cast<int>(body_x);
  position.y = static_cast<int>(body_y);
  return position;
}
