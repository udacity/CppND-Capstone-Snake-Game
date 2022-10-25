#ifndef GAME_H
#define GAME_H

#include <random>
#include <thread>
#include <vector>
#include <memory>
#include "SDL.h"
#include "channel.h"
#include "settings.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "player.h"

namespace SnakeGame
{

  class Game
  {
  public:
    Game(std::size_t grid_width, std::size_t grid_height, bool demo_mode, std::size_t num_of_players);
    void Run(Renderer &renderer,
             std::size_t target_frame_duration);
    int GetScore() const;
    int GetSize() const;

    std::string GetScoreForPlayers() const;

  private:
        struct TitleOutput {
          void operator()(std::shared_ptr<Player> const & player) {
            ++i;
            title_ += "Player: ";
            title_ += std::to_string(i);
            title_ += " Score: ";
            title_ += std::to_string(player->GetScore());
            title_ += " ";
          }
          std::string title_{};
          int i{0};
        };

    std::vector<std::shared_ptr<Player>> players_;  // owned
    SDL_Point food_;

    std::random_device randDev_;
    std::mt19937 randEngine_;
    std::uniform_int_distribution<int> randomWidth_;
    std::uniform_int_distribution<int> randomHeight_;

    int score_{0};
    Channel<Message> chan_{};
    std::vector<std::thread> threads_;

    void PlaceFood();
    void Update();
    void SpawnPlayers();
    void StartControl(Message &msg);
    void WaitForPlayers();
    SnakeGame::KeyStroke VerifySDLEvent();
  };
}
#endif