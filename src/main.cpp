#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  constexpr std::size_t nPlayers{2};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight, nPlayers);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  auto scores = game.GetScore();
  auto sizes  = game.GetSize();
  for (std::size_t i = 0; i < scores.size(); i++) {
    std::cout << "Player " << (i + 1)
              << " | Score: " << scores[i]
              << " | Size: "  << sizes[i] << "\n";
  }
  return 0;
}