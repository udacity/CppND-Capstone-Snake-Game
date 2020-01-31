#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      snake2(grid_width, grid_height, 1, 1, 0.0),
      snake3(grid_width, grid_height, 15, 15, 0.025),
      // snake3(grid_width, grid_height, 8, 8, 0.05, 5),
      engine(dev()), // Abel-Q1
      random_w(1, static_cast<int>(grid_width)-1),
      random_h(1, static_cast<int>(grid_height)-1), 
      random_dir1(0, 100),
      random_dir2(0, 100) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks(); // Abel-Q2
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration=0;
  int frame_count = 0;
  bool running = true;

  // Welcome screen
  frame_start = SDL_GetTicks(); 
  while (frame_duration<2000) {
    initGame(controller, renderer);
    frame_end = SDL_GetTicks();
    frame_duration = frame_end - frame_start;
  }

  while (running) {
    frame_start = SDL_GetTicks(); // unit: msec
    
    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, snake2, snake3, food);

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

void Game::initGame(Controller const &controller, Renderer &renderer) {
  renderer.initRender();
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
      // std::cout << "Food x = " << x << std::endl;
      // std::cout << "Food y = " << y << std::endl;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();
  // Update snake2: move in x
  // Controller::ChangeDirection(snake2, Snake::Direction::kLeft, Snake::Direction::kRight);
  // snake2.direction = Snake::Direction::kRight; //Abel
  // snake2.Update();
  // snake2.direction = Snake::Direction(random_dir1(engine));
  // if (snake2.direction==Snake::Direction::kUp || snake2.direction==Snake::Direction::kDown) 
  // {
  //   snake2.direction = Snake::Direction(random_dir1(engine)+2);
  // }  
  snake2.Update();
  int rand_dir2 = random_dir1(engine);
  if (rand_dir2%47==0) {
    if (snake2.direction==Snake::Direction::kUp || snake2.direction==Snake::Direction::kDown) {
      snake2.direction = Snake::Direction(rand_dir2%2+2);
    }  
    else {
      snake2.direction = Snake::Direction(rand_dir2%2);
    }
  }
  // if (int(snake2.direction)<=1) {
  //   rand_dir2 = random_dir1(engine)+2;
  // }
  // else {
  //   rand_dir2 = random_dir1(engine);
  // }
  // snake2.direction = Snake::Direction(rand_dir2);
  // std::cout << "snake2.direction = " << rand_dir2 << std::endl;
  // snake3.direction = Snake::Direction::kUp; //Abel
  // snake3.Update();
  // int rand_dir3;
  // if (rand_dir3<=1) {
  //   rand_dir3 = random_dir2(engine)+2;
  // }
  // else {
  //   rand_dir3 = random_dir2(engine);
  // }
  // snake3.direction = Snake::Direction(rand_dir3);
  // std::cout << "snake3.direction = " << rand_dir3 << std::endl;
  // snake3.Update();
  // snake3.direction = Snake::Direction(random_dir2(engine));
  // if (snake3.direction==Snake::Direction::kUp || snake3.direction==Snake::Direction::kDown) 
  // {
  //   snake3.direction = Snake::Direction(random_dir2(engine)+2);
  // }  
  // std::cout << "snake3.direction = " << int(snake3.direction) << std::endl;
  // if the snake runs into any part of snake2, it dies
  // std::cout << "snake.head_x = " << snake.head_x << std::endl;
  // std::cout << "snake2.head_x = " << snake2.head_x << std::endl;
  // std::cout << "snake.head_y = " << snake.head_y << std::endl;
  // std::cout << "snake2.head_y = " << snake2.head_y << std::endl;
  snake3.Update();
  int rand_dir3 = random_dir2(engine);
  if (rand_dir3%47==0) {
    if (snake3.direction==Snake::Direction::kUp || snake3.direction==Snake::Direction::kDown) {
      snake3.direction = Snake::Direction(rand_dir3%2+2);
    }  
    else {
      snake3.direction = Snake::Direction(rand_dir3%2);
    }
  }

  bool isSnake2Crash = false;
  // if (abs(snake.head_x-snake2.head_x)<0.1 && abs(snake.head_y-snake2.head_y)<0.1) {
  //   isSnake2Crash = true;
  // }
  // for (auto const &item : snake2.body) {
  //   if (abs(snake.head_x-item.x)<0.1 && abs(snake.head_y-item.y)<0.1) {
  //     isSnake2Crash = true;
  //   }
  // }

  bool isSnake3Crash = false;
  if (abs(snake.head_x-snake3.head_x)<0.01 && abs(snake.head_y-snake3.head_y)<0.01) {
    isSnake3Crash = true;
  }
  for (auto const &item : snake3.body) {
    if (abs(snake.head_x-item.x)<0.01 && abs(snake.head_y-item.y)<0.01) {
      isSnake3Crash = true;
    }
  }

  if (isSnake2Crash) {
    std::cout << "Crashed into snake2" << std::endl;
    snake.alive = false;
  }
  else if (isSnake3Crash) {
    std::cout << "Crashed into snake3" << std::endl;
    snake.alive = false;
  }
  else {
    for (auto const &item : snake.body) {
      if (abs(snake.head_x-item.x)<0.01 && abs(snake.head_y-item.y)<0.01) {
        std::cout << "Crashed into itself" << std::endl;
        std::cout << "snake.head_x = " << snake.head_x << std::endl;
        std::cout << "snake.head_y = " << snake.head_y << std::endl;
        std::cout << "item.x = " << item.x << std::endl;
        std::cout << "item.y = " << item.y << std::endl;
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
    snake3.GrowBody(); //Abel
    // snake.speed += 0.02;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }

// //Abel
// void StartTrain() {
// }