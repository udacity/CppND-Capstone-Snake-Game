#include "game.h"
#include <iostream>
#include <chrono>
#include "SDL.h"

Game::Game(std::size_t width, std::size_t height, std::size_t cols, std::size_t rows)
    : renderer(width, height, cols, rows),
      controller(Controller()),
      runner(cols / 2, rows - 2),
      engine(dev()),
      random_x(0, static_cast<int>(cols - 1)),
      random_type(0, 100)
{
  GenerateObstacles();
}

void Game::Run(std::size_t target_frame_duration)
{
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, this);
    Update();
    renderer.Render(runner, obstacles);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(GetScore(), frame_count);
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

void Game::CleanObstacles()
{
    auto part = std::partition(obstacles.begin(), obstacles.end(),
        [&](const ObstacleItr &ob) { return ob->active && ob->GetY() <= renderer.Rows(); });
    obstacles.erase(part, obstacles.end());
}

void Game::GenerateObstacles()
{
  /*
  [0, 50) nothing happens
  [50, 85) rock
  [85, 90) shield
  [90, 100]  coin
  */
  int type = random_type(engine());
  int x = random_x(engine());
  int y = 0;
  if (50 <= type && type < 85)
  {
    obstacles.emplace_back(std::make_unique<Rock>(x, y));
  }
  else if (85 <= type && type < 90)
  {
    obstacles.emplace_back(std::make_unique<Shield>(x, y));
  }
  else if (90 <= type)
  {
    obstacles.emplace_back(std::make_unique<Coin>(x, y));
  }
}

void Game::Update() {
  if (!runner.Active()) return;

  runner.Update();

  for (ObstacleItr &ob : obstacles)
  {
    if (ob->Collide(runner))
    {
      ob->HitRunner(runner);
    }
    ob->Update();
  }

  CleanObstacles();
  GenerateObstacle();
}

int Game::Score() const { return runner.Coin(); }

void Game::ShiftRunner(int delta)
{
  float target = runner.GetX() + delta;
  if (0 <= target && target <= renderer.Cols())
  {
    runner.SetX(target);
  }
}