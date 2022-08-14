#include "game.h"
#include "SDL.h"
#include <string>
#include "route_planner.h"
#include <iostream>
namespace SnakeGame
{
  Game::Game(std::size_t grid_width, std::size_t grid_height, bool demo_mode)
      : randEngine_(randDev_()),
        randomWidth_(0, static_cast<int>(grid_width - 1)),
        randomHeight_(0, static_cast<int>(grid_height - 1))
  {
    players_.emplace_back(std::make_unique<Player>(grid_width,grid_height,demo_mode));

    PlaceFood();
  }

  void Game::Run(Controller const &controller, Renderer &renderer,
                 std::size_t target_frame_duration)
  {
    Uint32 title_timestamp{SDL_GetTicks()};
    Uint32 frame_start{0};
    Uint32 frame_end{0};
    Uint32 frame_duration{0};
    int frame_count{0};
    bool isRunning{true};
    
    while (isRunning)
    {
      frame_start = SDL_GetTicks();

      auto runPlayer = [&](std::unique_ptr<Player>const &player) {
        player->run(food_);
      };

      std::for_each(players_.cbegin(),players_.cend(),runPlayer);

      auto checkPlayerTerminated = [&](std::unique_ptr<Player> const &player) {
        return (false == player->IsSnakeRunning());
      };

      if (std::any_of(players_.cbegin(),players_.cend(),checkPlayerTerminated)) {
        isRunning = false;
      }


      // Input, Update, Render - the main game loop.
      Update();

      renderer.RenderStart();
      renderer.RenderFood(food_);

      auto renderPlayer = [&](std::unique_ptr<Player>const &player) {
        renderer.RenderSnake(player->GetSnake());
      };
      std::for_each(players_.cbegin(),players_.cend(),renderPlayer);

      renderer.RenderEnd();
//      renderer.Render(players_[0]->GetSnake(), food_);

      frame_end = SDL_GetTicks();

      // Keep track of how long each loop through the input/update/render cycle
      // takes.
      ++frame_count;
      frame_duration = frame_end - frame_start;

      // After every second, update the window title.
      if (frame_end - title_timestamp >= 1000U)
      {
        struct TitleOutput {
          void operator()(std::unique_ptr<Player> const & player) {
            ++i;
            title_ += std::to_string(i);
            title_ += " Score: ";
            title_ += std::to_string(player->GetScore());
            title_ += " ";
          }
          std::string title_{"Player: "};
          int i{0};
        };
        TitleOutput output = std::for_each(players_.cbegin(),players_.cend(),TitleOutput());

        renderer.UpdateWindowTitle(output.title_);
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
    }
  }

  void Game::PlaceFood()
  {
    while (true)
    {
      const auto x = randomWidth_(randEngine_);
      const auto y = randomHeight_(randEngine_);
      // Check that the location is not occupied by a snake item before placing
      // food_.

      auto checkFoodIsOccupied = [&](std::unique_ptr<Player> const &player) {
        return (true == player->GetSnake()->SnakeCell(x, y));
      };

      if (std::none_of(players_.cbegin(),players_.cend(),checkFoodIsOccupied)) {
        food_.x = x;
        food_.y = y;
        return;
      }
    }
  }

  void Game::Update()
  {
    auto checkAnyPlayerisDead = [&](std::unique_ptr<Player> const &player) {
      return (false == player->GetSnake()->isAlive_);
    };

    if (std::any_of(players_.cbegin(),players_.cend(),checkAnyPlayerisDead)) {
      return;
    }

    std::for_each(players_.cbegin(),players_.cend(),[&](std::unique_ptr<Player> const &player) {
      player->GetSnake()->Update();
    });

    auto CheckPlayersEatFood = [&](std::unique_ptr<Player> const &player) {
      return (true == player->CheckSnakeEatsFood(food_));
    };

    if (std::any_of(players_.cbegin(),players_.cend(),CheckPlayersEatFood)) {
      PlaceFood();
    }

  }

  int Game::GetScore() const { return score_; }
  int Game::GetSize() const { return players_[0]->GetSnake()->size_; }
}