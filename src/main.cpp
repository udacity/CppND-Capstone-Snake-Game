#include <iostream>
#include "game.h"
#include "controller.h"
#include "renderer.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{200};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridCols{10}; // x
  constexpr std::size_t kGridRows{32}; // y

  Controller controller;
  Renderer renderer(kScreenWidth, kScreenHeight, kGridCols, kGridRows);
  Game game(kGridCols, kGridRows);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  return 0;
}