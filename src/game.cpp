#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      snake2(grid_width, grid_height, 1, 1, 10, 0.05),
      engine(dev()), // Abel-Q1
      random_w(1, static_cast<int>(grid_width)-1),
      random_h(1, static_cast<int>(grid_height)-1) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks(); // Abel-Q2
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, snake2, food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y) && !snake2.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;  
      std::cout << "Food x = " << x << std::endl;
      std::cout << "Food y = " << y << std::endl;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();
  // Update snake2: move in x
  // Controller::ChangeDirection(snake2, Snake::Direction::kLeft, Snake::Direction::kRight);
  snake2.direction = Snake::Direction::kRight; //Abel
  snake2.Update();
  // if the snake runs into any part of snake2, it dies
  // std::cout << "snake.head_x = " << snake.head_x << std::endl;
  // std::cout << "snake2.head_x = " << snake2.head_x << std::endl;
  // std::cout << "snake.head_y = " << snake.head_y << std::endl;
  // std::cout << "snake2.head_y = " << snake2.head_y << std::endl;

  if (abs(snake.head_x-snake2.head_x)<1 && abs(snake.head_y-snake2.head_y)<1) {
    snake.alive = false;
  }
  else {
    for (auto const &item : snake2.body) {
      if (abs(snake.head_x-item.x)<1 && abs(snake.head_y-item.y)<1) {
        snake.alive = false;
      }
    } 
  }

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    std::cout << "Just ate a food!" << std::endl;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake2.GrowBody(); //Abel
    // snake.speed += 0.02;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }

// //Abel
// void StartTrain() {
// }