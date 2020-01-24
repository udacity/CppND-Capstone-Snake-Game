#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h" 

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{480}; // Size of the screen 
  constexpr std::size_t kScreenHeight{480};
  constexpr std::size_t kGridWidth{16}; // Number of grid 
  constexpr std::size_t kGridHeight{16};

  // Create renderer, controller and game objects
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  // Run the game
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}