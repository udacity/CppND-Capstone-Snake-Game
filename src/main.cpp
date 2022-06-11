#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "configfileparser.h"

int main(int const argc, char const*const* argv)
{
  if (argc > 3) {
    std::cerr << "Not more than one arguments! Just the config file is needed!\n";
  }
  const auto filename  = std::string(argv[1]);
  std::cout << "filename " << filename << " GetGridWidth "  <<  SnakeGame::GetGridWidth(filename) << "\n";

  SnakeGame::Renderer renderer(SnakeGame::GetScreenWidth(filename), SnakeGame::GetScreenHeight(filename), SnakeGame::GetGridWidth(filename), SnakeGame::GetGridHeight(filename));
  SnakeGame::Controller controller;
  SnakeGame::Game game(SnakeGame::GetGridWidth(filename), SnakeGame::GetGridHeight(filename));
  game.Run(controller, renderer, SnakeGame::GetMsPerFrame(filename));
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}
