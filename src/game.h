#ifndef GAME_H
#define GAME_H

#include <vector>
#include <random>
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "SDL.h"
//#include "SDL_image.h"

class Game {

  public:

    Game(const std::size_t &grid_width, const std::size_t &grid_height);
    void Run(Controller &controller, Renderer &renderer, const std::size_t &ms_per_frame);
    int GetScore() const;
    int GetSize() const;

  private:

    const std::size_t kGridWidth;
    const std::size_t kGridHeight;

    Snake snake;
    SDL_Point food;

    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_w {0, static_cast<int>(kGridWidth)};
    std::uniform_int_distribution<int> random_h {0, static_cast<int>(kGridHeight)};

    int score = 0;

    void PlaceFood();
    void Update();
    void PollEvents();

};

#endif