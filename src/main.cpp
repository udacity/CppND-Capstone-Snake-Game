#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "settings.h"
#include "configfileparser.h"

int main()
{
  std::cout << "screen from file " << SnakeGame::GetScreenHeight() << "\n";
  std::cout << "GetScreenWidth from file " << SnakeGame::GetScreenWidth() << "\n";
  std::cout << "GetGridHeight from file " << SnakeGame::GetGridHeight() << "\n";
  std::cout << "GetGridWidth from file " << SnakeGame::GetGridWidth() << "\n";
  std::cout << "GetNoOfSnakes from file " << SnakeGame::GetNoOfSnakes() << "\n";

  SnakeGame::Renderer renderer(SnakeGame::kScreenWidth, SnakeGame::kScreenHeight, SnakeGame::kGridWidth, SnakeGame::kGridHeight);
  SnakeGame::Controller controller;
  SnakeGame::Game game(SnakeGame::kGridWidth, SnakeGame::kGridHeight);
  game.Run(controller, renderer, SnakeGame::kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}
