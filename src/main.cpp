#include <iostream>
#include "game.h"
#include "renderer.h"
#include "configfileparser.h"

class Vehicle
{
public:
    Vehicle() : _id(0) {}
    void addID(int id) { _id = id; }
    void printID()
    {
        std::cout << "Vehicle ID=" << _id << std::endl;
    }

private:
    int _id;
};

void printHello()
{
    // perform work
    std::cout << "Hello from Worker thread #" << std::this_thread::get_id() << " \n";
}

int main(int const argc, char const*const* argv)
{

  if (argc > 3) {
    std::cerr << "Not more than one arguments! Just the config file is needed!\n";
    return 0;
  }

  std::string filename;
  if (argc == 1) {
    filename = SnakeGame::kDefaultFileName;
  } else {
    filename  = std::string(argv[1]);
  }

  SnakeGame::Renderer renderer(SnakeGame::GetScreenWidth(filename), SnakeGame::GetScreenHeight(filename), SnakeGame::GetGridWidth(filename), SnakeGame::GetGridHeight(filename));
  SnakeGame::Game game(SnakeGame::GetGridWidth(filename), SnakeGame::GetGridHeight(filename), SnakeGame::GetDemoMode(filename), SnakeGame::GetNoOfSnakes(filename));
  game.Run(renderer, SnakeGame::GetMsPerFrame(filename));
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";

  return 0;
}
