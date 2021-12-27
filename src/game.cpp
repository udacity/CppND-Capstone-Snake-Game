#include "game.h"
#include <iostream>
#include <algorithm>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "utility.h"

Game::Game(std::size_t cols, std::size_t rows)
    : cols(cols),
      rows(rows),
	  runner(cols / 2, rows - 2),
      random_x(0, static_cast<int>(cols - 1)),
      random_type(0, 10),
      random_time(1000, 2500),
      obTimer(TimeChecker())
{
  GenerateObstacles();
}

void Game::Run(const Controller &controller, Renderer &renderer,
               std::size_t target_frame_duration)
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
    controller.HandleInput(running, runner);
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
        [&](const ObstaclePtr &ob) { return ob->GetActive() && ob->GetY() <= rows; });
    obstacles.erase(part, obstacles.end());
}

void Game::GenerateObstacles()
{
  /*
  [0, 5] rock
  [6, 8] shield
  [9, 10]  coin
  */
  int type = random_type();
  float x = static_cast<float>(random_x());

  if (0 <= type && type <= 5)
  {
    obstacles.emplace_back(std::make_unique<Rock>(x));
  }
  else if (6 <= type && type <= 8)
  {
    obstacles.emplace_back(std::make_unique<Shield>(x));
  }
  else if (9 <= type)
  {
    obstacles.emplace_back(std::make_unique<Coin>(x));
  }
}

void Game::Update()
{
  if (!runner.GetActive()) return;

  runner.Update();

  for (ObstaclePtr &ob : obstacles)
  {
    if (ob->Collide(&runner))
    {
      ob->HitRunner(runner);
    }
    ob->Update();
  }

  CleanObstacles();
  if (!obTimer.GetActive() || obTimer.DurationPassed())
  {
    GenerateObstacles();
    obTimer.SetDuration(random_time());
    obTimer.Start();
  }
}

int Game::GetScore() const { return runner.GetCoin(); }