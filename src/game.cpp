#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height, int num_players) :
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {

  SetNumPlayers(num_players);
  // Create snakes
  for (int i = 0; i < n_players; i++) {
    int dx = (i - (n_players - 1) / 2.0) * (grid_width / 4);  // space them evenly
    int dy = 0;  // keep them centered vertically
    snakes.push_back(std::make_unique<Snake>(grid_width, grid_height, dx, dy));
  }
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snakes);
    Update();
    renderer.Render(snakes, food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(scores, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::Update() {
  for (std::size_t i = 0; i < snakes.size(); i++) {
    // Skip a snake if not alive
    if (!(snakes[i]->alive)) continue;
    // Otherwise update it
    snakes[i]->Update();
    // Check if it ate the food
    int new_x = static_cast<int>(snakes[i]->head_x);
    int new_y = static_cast<int>(snakes[i]->head_y);
    if (food.x == new_x && food.y == new_y) {
      // Add a new food
      PlaceFood();
      // Update the scores
      scores[i]++;
      // Grow snake and increase speed.
      snakes[i]->GrowBody();
      snakes[i]->speed += 0.02;
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (std::none_of(snakes.begin(), snakes.end(),
        [&](auto &s){ return s->SnakeCell(x, y); })) {
      food = {x, y};
      return;
    }
  }
}


std::vector<int> Game::GetSize() const {
  std::vector<int> sizes;
  sizes.reserve(snakes.size());
  for (auto const& s : snakes) {
    sizes.push_back(s ? s->size : 0);
  }
  return sizes;
}