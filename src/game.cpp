#include "game.h"
#include <iostream>
#include <mutex>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : actor(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width)),
      random_h(0, static_cast<int>(grid_height)) 
{
  PlaceFood();
  PlaceEnemies(grid_width, grid_height);
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) 
{
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  for(auto i = enemies.begin(); i != enemies.end(); ++i)
  {
        i->get()->UpdatePosition();
  }
  
  while (running) 
  {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, actor);
    Update();
    renderer.Render(actor, food, enemies);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) 
    {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) 
    {
      SDL_Delay(target_frame_duration - frame_duration);
    }

    if (!actor.alive) running = false;
  }
}

void Game::PlaceFood() 
{
  int x, y;
  while (true) 
  {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a actor item before placing
    // food.
    if (actor.body_x != x || actor.body_y != y) 
    {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::PlaceEnemies(std::size_t grid_width, std::size_t grid_height) 
{
  int x, y;
  int i = 0;
  while (i < 5) 
  {
    std::unique_lock<std::mutex> lck(mtx);
    x = random_w(engine);
    y = random_h(engine);

    // Check that the location is not occupied by a actor item before placing
    // enemy. If it is occupied by food, it's not a problem since enemy is moving.
    if (actor.body_x != x || actor.body_y != y) 
    {
      SDL_Point position;
      position.x = x;
      position.y = y;
      
      Enemy::Direction direction;
      int rand_direction = 1 + (rand() % 4); // based on the recommendation from https://www.bitdegree.org/learn/random-number-generator-cpp
      switch (rand_direction)
      {
      case 2:
        direction = Enemy::Direction::kLeft;
        break;

      case 3:
        direction = Enemy::Direction::kRight;
        break;

      case 4:
        direction = Enemy::Direction::kDown;
        break;
      
      default:
        direction = Enemy::Direction::kUp;
        break;
      }
      enemies.emplace_back(std::make_unique<Enemy>(position, direction, grid_width, grid_height));
      i++;
      return;
    }
    lck.unlock();
  }
}

void Game::Update() 
{
  if (!actor.alive) return;

  actor.Update();

  int new_x = static_cast<int>(actor.body_x);
  int new_y = static_cast<int>(actor.body_y);

  // Check if there're enemies over here
  for(auto i = enemies.begin(); i != enemies.end(); ++i)
  {
    i->get()->UpdatePosition();
    if (static_cast<int>(i->get()->body_x) == new_x && static_cast<int>(i->get()->body_y) == new_y) 
    {
      actor.alive = false;
      break;
    }
  }

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) 
  {
    score++;
    PlaceFood();
    // Increase actor's speed.
    actor.speed += 0.02;
  }
}

int Game::GetScore() const { return score; }
