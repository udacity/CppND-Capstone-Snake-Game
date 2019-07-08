#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"


int main() {

    const std::size_t kFramesPerSecond = 60;
    const std::size_t kMsPerFrame   = 1000 / kFramesPerSecond;
    const std::size_t kScreenWidth  = 640;
    const std::size_t kScreenHeight = 640;
    const std::size_t kGridWidth    = 32;
    const std::size_t kGridHeight   = 32;

    Renderer renderer(kScreenWidth, kScreenHeight, kGridHeight, kGridHeight);
    Controller controller;
    Game game(kGridWidth, kGridHeight);
    game.Run(controller, renderer, kMsPerFrame);
    std::cout << "Game has terminated successfully, score: " << game.GetScore() << ", size: " << game.GetSize() << "\n";
    return 0;
}