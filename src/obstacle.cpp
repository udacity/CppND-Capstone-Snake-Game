#include "obstacle.h"

// -------------------- OBSTACLE --------------------

void Obstacle::Update()
{
    switch (direction) {
        case Direction::kUp:
        head_y -= speed;
        break;

        case Direction::kDown:
        head_y += speed;
        break;
    }
}

void Obstacle::HitRunner(Runner &runner)
{
    Active(false);
}

// -------------------- SHIELD --------------------
// TODO: Add colours

// #0E9594
Shield::Shield(float x, float y):
    Obstacle(x, y),
    color(14, 149, 148, 255)
{}

void Shield::HitRunner(Runner &runner)
{
    Obstacle::HitRunner(runner);
    runner.Shielded(true);
}

// -------------------- COIN --------------------

// #FCBA04
Coin::Coin(float x, float y): 
    Obstacle(x, y),
    color(252, 186, 4, 244)
{}

void Coin::HitRunner(Runner &runner)
{
    Obstacle::HitRunner(runner);
    runner.IncrementCoin();
}

// -------------------- ROCK --------------------

// #7B2D26
Rock::Rock(float x, float y): 
    Obstacle(x, y),
    color(123, 45, 38, 255)
{}

void Rock::HitRunner(Runner &runner)
{
    Obstacle::HitRunner(runner);
    if (!runner.Shielded())
    {
        runner.Active(false);        
    }
}