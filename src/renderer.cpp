#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(const std::vector<std::unique_ptr<Snake>> &snakes,
                      SDL_Point const &food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render each snake
  for (std::size_t i = 0; i < snakes.size(); i++) {
    auto &s = snakes[i];
    if (!s) continue;

    // Give each snake a different body color
    if (i == 0)
      SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF); // white
    else
      SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xFF, 0x00, 0xFF); // green

    // Body
    for (SDL_Point const &point : s->body) {
      block.x = point.x * block.w;
      block.y = point.y * block.h;
      SDL_RenderFillRect(sdl_renderer, &block);
    }

    // Head
    block.x = static_cast<int>(s->head_x) * block.w;
    block.y = static_cast<int>(s->head_y) * block.h;
    if (s->alive) {
      if (i == 0)
        SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF); // blue head
      else
        SDL_SetRenderDrawColor(sdl_renderer, 0xAA, 0xAA, 0xAA, 0xFF); // grey head 
    } else {
      SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF); // red if dead
    }
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(const std::vector<int> &scores, int fps) {
  // Player scores
  std::string title{"Snake Scores: "};
  for (std::size_t i = 0; i < scores.size(); i++) {
    title += "P" + std::to_string(i+1) + "=" + std::to_string(scores[i]) + "   ";
  }
  // Frames per second
  title += "FPS: " + std::to_string(fps);

  SDL_SetWindowTitle(sdl_window, title.c_str());
}

int Renderer::ShowPlayerMenu() {
  bool in_menu = true;
  int selected = 1; // 1P by default

  // basic layout
  SDL_Rect left, right, title;
  left.w  = screen_width / 3;
  left.h  = screen_height / 3;
  left.x  = screen_width / 6;
  left.y  = screen_height / 2 - left.h / 2;

  right    = left;
  right.x  = screen_width - left.x - left.w;

  title.x = 0; title.y = screen_height / 8;
  title.w = screen_width; title.h = screen_height / 10;

  while (in_menu) {
    // --- input ---
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) return 1; // fallback to 1P if window closed
      if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
          case SDLK_LEFT:  selected = 1; break;
          case SDLK_RIGHT: selected = 2; break;
          case SDLK_RETURN:
          case SDLK_KP_ENTER:
            return selected;
          case SDLK_1: return 1;
          case SDLK_2: return 2;
        }
      }
    }

    // --- draw ---
    SDL_SetRenderDrawColor(sdl_renderer, 0x12, 0x12, 0x12, 0xFF); // bg
    SDL_RenderClear(sdl_renderer);

    // title bar
    SDL_SetRenderDrawColor(sdl_renderer, 0x22, 0x22, 0x22, 0xFF);
    SDL_RenderFillRect(sdl_renderer, &title);

    // left panel (1P)
    if (selected == 1) SDL_SetRenderDrawColor(sdl_renderer, 0x33, 0x88, 0xCC, 0xFF);
    else               SDL_SetRenderDrawColor(sdl_renderer, 0x33, 0x33, 0x33, 0xFF);
    SDL_RenderFillRect(sdl_renderer, &left);

    // right panel (2P)
    if (selected == 2) SDL_SetRenderDrawColor(sdl_renderer, 0x33, 0x88, 0xCC, 0xFF);
    else               SDL_SetRenderDrawColor(sdl_renderer, 0x33, 0x33, 0x33, 0xFF);
    SDL_RenderFillRect(sdl_renderer, &right);

    // decorative “snake heads” to indicate 1P vs 2P
    auto draw_head = [&](int cx, int cy){
      SDL_Rect head{cx-12, cy-12, 24, 24};
      SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
      SDL_RenderFillRect(sdl_renderer, &head);
    };
    draw_head(left.x + left.w/2,  left.y + left.h/2);               // 1 head
    draw_head(right.x + right.w/2 - 18, right.y + right.h/2);       // 2 heads
    draw_head(right.x + right.w/2 + 18, right.y + right.h/2);

    SDL_RenderPresent(sdl_renderer);
    SDL_Delay(16); // ~60 FPS
  }
  return selected; // not reached, but keeps compiler happy
}
