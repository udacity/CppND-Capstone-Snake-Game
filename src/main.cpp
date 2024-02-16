#include <iostream>
#include <future>
#include <thread>
#include <string>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "leaderboard.h"

#undef main

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  // Get the Leaderboard in the backgrond
  std::promise<Leaderboard> p;
  std::future<Leaderboard> f = p.get_future();
  std::thread t([&p] {p.set_value(Leaderboard()); });

  std::string name;
  std::cout << "Enter your name: ";
  std::cin >> name;

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);

  std::cout << "Game has terminated successfully!\n";

  std::cout << "You scored " << game.GetScore() << "\n";


  // Get the Leaderboard from the future
  Leaderboard leaderboard = f.get();
  t.join();
  leaderboard.addRecord(Record(game.GetScore(), name));
  leaderboard.saveRecords();
  leaderboard.printRecords(10);

  return 0;
}