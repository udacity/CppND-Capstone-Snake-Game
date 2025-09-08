#include <iostream>

#include "game.h"
#include "SDL.h"

Game::Game(std::size_t grid_w, std::size_t grid_h, int num_players, Uint32 inactivity_timout) :
      grid_width(grid_w),
      grid_height(grid_h),
      inactivity_ms(inactivity_timout),
      engine(dev()),
      random_w(0, static_cast<int>(grid_w - 1)),
      random_h(0, static_cast<int>(grid_h - 1)),
      grid_model(grid_w, grid_h) {

  // N of players
  SetNumPlayers(num_players);
  // Concurrency
  plan_futures.resize(n_players);
  planned_goal.assign(n_players, {-1, -1});
  // Inactivity settings
  last_input_ms.assign(n_players, SDL_GetTicks());
  // Spawn snakes
  for (int i = 0; i < n_players; i++) {
    int dx = (i - (n_players - 1) / 2.0) * (grid_width / 4);  // space them evenly
    int dy = 0;  // keep them centered vertically
    snakes.push_back(std::make_unique<Snake>(grid_width, grid_height, dx, dy));
  }
  // Place objective food
  PlaceFood();
  grid_model.MarkFood(food.x, food.y);
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
    controller.HandleInput(running, snakes, last_input_ms);
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
    // SNAKES STATUS UPDATE

    // Skip a snake if not alive
    if (!(snakes[i]->alive)) continue;
    // Mode switching based on inactivity / recent input
    Uint32 now = SDL_GetTicks();
    bool inactive = (now - last_input_ms[i] >= inactivity_ms);
    if (inactive && !(snakes[i]->IsAutonomous())) {
      snakes[i]->SetMode(Snake::Mode::Autonomous);
      snakes[i]->ClearPlannedPath();  // force fresh plan
    } else if (!inactive && snakes[i]->IsAutonomous()) {
      // A key was pressed recently for this player
      snakes[i]->SetMode(Snake::Mode::Manual);
      snakes[i]->ClearPlannedPath();
    }
    // Autonomous planning if needed (async, non-blocking)
    if (snakes[i]->IsAutonomous()) {
      // Only submit if: (a) we have no valid path, AND (b) no job already running.
      if ( (!snakes[i]->HasPlannedPath() || snakes[i]->replan_requested)
          && !plan_futures[i].valid() ) {
        snakes[i]->replan_requested = false;
        snakes[i]->ClearPlannedPath();
        SubmitPlan(i);  // Trigger planning
      }

      // Try to install any finished plan this frame
      TryInstallPlan(i);
    }

    // SNAKES UPDATE
    snakes[i]->Update();

    // FOOD & STATS UPDATE
    int new_x = static_cast<int>(snakes[i]->head_x);
    int new_y = static_cast<int>(snakes[i]->head_y);
    if (food.x == new_x && food.y == new_y) {
      // Add a new food
      PlaceFood();
      // Update model
      grid_model.Reset();
      grid_model.MarkFood(food.x, food.y);
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

void Game::SubmitPlan(std::size_t i) {
  Snake &s = *snakes[i];

  // Build a temporary grid, local to the async task (no races with grid_model)
  Grid temp(static_cast<int>(grid_width), static_cast<int>(grid_height));
  // Mark food (goal)
  temp.MarkFood(food.x, food.y);
  // Define start and goal
  const int sx = static_cast<int>(s.head_x);
  const int sy = static_cast<int>(s.head_y);
  const int gx = food.x;
  const int gy = food.y;
  planned_goal[i] = {gx, gy}; // remember which goal this plan targets

  // Submit A* planning async task (ownership of temporary grid)
  plan_futures[i] = std::async(std::launch::async,
    [sx, sy, gx, gy, temp = std::move(temp)]() mutable -> std::vector<std::pair<int,int>> {
      Node &snode = temp.At(sx, sy);
      Node &gnode = temp.At(gx, gy);

      RoutePlanner planner(temp, &snode, &gnode);
      planner.AStarSearch();

      // Return coordinate path (safe across threads)
      return planner.GetPlanCells();
    }
  );
}

void Game::TryInstallPlan(std::size_t i) {
  auto &fut = plan_futures[i];
  if (!fut.valid()) return;

  using namespace std::chrono_literals;
  if (fut.wait_for(0ms) != std::future_status::ready) return;

  std::vector<std::pair<int,int>> cells;
  try {
  cells = fut.get();
  } catch (const std::exception &e) {
    std::cerr << "Planning failed: " << e.what() << "\n";
    snakes[i]->replan_requested = true;  // try again next frame
    return; }

  // Only install if still autonomous and goal unchanged
  if (!snakes[i]->IsAutonomous()) return;
  if (planned_goal[i].first  != food.x ||
    planned_goal[i].second != food.y) {
    snakes[i]->replan_requested = true;
    return;
  }

  // Map coords -> live grid Node* and install
  std::vector<Node*> ptrs;
  ptrs.reserve(cells.size());
  for (auto &c : cells) {
    ptrs.push_back(&grid_model.At(c.first, c.second));
  }
  snakes[i]->SetPlannedPath(ptrs);
}

std::vector<int> Game::GetSize() const {
  std::vector<int> sizes;
  sizes.reserve(snakes.size());
  for (auto const& s : snakes) {
    sizes.push_back(s ? s->size : 0);
  }
  return sizes;
}