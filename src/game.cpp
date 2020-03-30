#include <chrono>
#include <iostream>
#include <thread>

#include "SDL.h"

#include "game.h"

Game::Game(std::size_t grid_width, std::size_t grid_height) :
    shooter(grid_width, grid_height),
    enemyShipManager(grid_width, grid_height) {}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;
    bool running = true;
    std::string windowTitle;

    while (running) {
        frame_start = SDL_GetTicks();

        // Input, Update, Render - the main game loop.
        controller.HandleInput(running, shooter);
        Update();
        
        if (gameOver) {
            renderer.RenderBlank();
            SDL_Delay(3000);
            break;
        } else if (levelUp) {
            levelUp = false;
            renderer.RenderBlank();
            SDL_Delay(3000);
        } else if (shooterHit) {
            shooterHit = false;
            renderer.RenderBlank();
            SDL_Delay(3000);
        } else {
            renderer.Render(shooter, enemyShipManager);
            frame_end = SDL_GetTicks();

            // Keep track of how long each loop through the input/update/render cycle
            // takes.
            frame_count++;
            frame_duration = frame_end - frame_start;

            // After every second, update the window title.
            if (frame_end - title_timestamp >= 1000) {
                windowTitle = "LVL: " + std::to_string(level) +
                              "  LIFE: " + std::to_string(shooter.life) +
                              "  SCORE: " + std::to_string(score) +
                              "  FPS: " + std::to_string(frame_count);
                renderer.UpdateWindowTitle(windowTitle);
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
}

void Game::Update() {
    shooter.Update();
    enemyShipManager.Update();
    
    if (enemyShipManager.enemyWin) {
        gameOver = true;
    }
    
    // check if enemy missiles hit the shooter
    shooterHit = shooter.ProcessEnemyMissiles(enemyShipManager.missiles);
    if (shooterHit) {
        if (!shooter.alive) {
            gameOver = true;
        }
        shooter.missiles.clear();
        enemyShipManager.missiles.clear();
        enemyShipManager.UpdateMissileTS();
    }
    
    // check if shooter missile hit any enemy ships
    int shipsHit = enemyShipManager.ProcessShooterMissiles(shooter.missiles);
    levelUp = enemyShipManager.ships.empty();
    
    score += shipsHit * (level * 10);
    
    if (levelUp) {
        score += level * 1000;
        level += 1;
        enemyShipManager.speed += 0.1f;
        enemyShipManager.missileWaitTime *= 0.9;
        
        shooter.missiles.clear();
        enemyShipManager.createShips(); // Updates MissileTS as well
        enemyShipManager.missiles.clear();
    }
    
}

int Game::GetScore() const { return score; }
//int Game::GetSize() const { return shooter.size; }
