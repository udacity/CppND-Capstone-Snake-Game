#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "settings.h"
#include "configfileparser.h"

int main()
{
  SnakeGame::Renderer renderer(SnakeGame::GetScreenWidth(), SnakeGame::GetScreenHeight(), SnakeGame::GetGridWidth(), SnakeGame::GetGridHeight());
  SnakeGame::Controller controller;
  SnakeGame::Game game(SnakeGame::GetGridWidth(), SnakeGame::GetGridHeight());
  game.Run(controller, renderer, SnakeGame::kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}
