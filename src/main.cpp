#include <iostream>
#include "game.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{200};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridCols{10}; // x
  constexpr std::size_t kGridRows{32}; // y

  Game game(kScreenWidth, kScreenHeight, kGridCols, kGridRows);
  game.Run(kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  return 0;
}