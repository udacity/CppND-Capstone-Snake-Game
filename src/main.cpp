#include <iostream>
#include "game.h"
#include "controller.h"
#include "renderer.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{400};
  constexpr std::size_t kScreenHeight{400};
  constexpr std::size_t kGridCols{20}; // x
  constexpr std::size_t kGridRows{20}; // y
  // grid sizes = 20 x 20

  Controller controller;
  Renderer renderer(kScreenWidth, kScreenHeight, kGridCols, kGridRows);
  Game game(kGridCols, kGridRows);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  return 0;
}