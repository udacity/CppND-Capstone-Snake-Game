#include <iostream>
#include "game.h"
#include "SDL.h"

Game::Game(const std::size_t &grid_width, const std::size_t &grid_height) : 
                    kGridWidth(grid_width), kGridHeight(grid_height), engine(dev()) {
    snake = Snake(grid_width, grid_height);
    PlaceFood();
}


void Game::Run(Controller &controller, Renderer &renderer, const std::size_t &ms_per_frame) {
    Uint32 frame_ms, start = SDL_GetTicks(), before, after;
    int frame_count = 0;
    bool running = true;

    while (running) {
        before = SDL_GetTicks();

        // Input, Update, Render - the main game loop.
        controller.HandleInput(running, snake);
        Update();
        renderer.Render(snake, food);

        after = SDL_GetTicks();

        // Keep track of how long each loop through the input/update/render cycle takes.
        frame_count++;
        frame_ms = after - before;

        if (after - start >= 1000) {
            renderer.UpdateWindowTitle(score, frame_count);
            frame_count = 0;
            start = after;
        }

        if (ms_per_frame > frame_ms) {
            SDL_Delay(ms_per_frame - frame_ms);
        }
    }
}


void Game::PlaceFood() {
    int x, y;
    while (true) {
        x = random_w(engine);
        y = random_h(engine);
        // Check that the location is not occupied by a snake item before placing food.
        if (!snake.SnakeCell(x,y)) {
            food.x = x;
            food.y = y;
            break;
        }
    }
}


int Game::GetSize() const {
    return snake.size;
}


void Game::Update() {
    if (!snake.alive)
        return;

    snake.Update();

    int new_x = static_cast<int>(snake.head_x);
    int new_y = static_cast<int>(snake.head_y);

    // Check if there's food over here
    if (food.x == new_x && food.y == new_y) {
        score++;
        PlaceFood();
        // Grow snake and increase speed.
        snake.GrowBody(1);
        snake.speed += 0.02;
    }

}


int Game::GetScore() const {
    return score;
}
