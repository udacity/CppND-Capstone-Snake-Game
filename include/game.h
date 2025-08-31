#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, int num_players);

  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  
  // Getters/Setters and invariants
  std::vector<int> GetSize() const;
  std::vector<int> GetScore() const { return scores; }
  void SetNumPlayers(const int &num_players) { 
    if (num_players < 1 || num_players > 2) {
        throw std::invalid_argument("The number of players must be 1 or 2");
    }
    n_players = num_players;
    scores.assign(n_players, 0);
  }

 private:
  int n_players;
  std::vector<std::unique_ptr<Snake>> snakes;
  SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  std::vector<int> scores;

  void PlaceFood();
  void Update();
};

#endif