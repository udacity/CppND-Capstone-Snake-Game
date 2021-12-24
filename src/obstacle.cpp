#include "obstacle.h"

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

void Shield::HitRunner(Runner &runner)
{
    Obstacle::HitRunner(runner);
    runner.Shielded(true);
}

void Coin::HitRunner(Runner &runner)
{
    Obstacle::HitRunner(runner);
    runner.IncrementCoin();
}

void Rock::HitRunner(Runner &runner)
{
    Obstacle::HitRunner(runner);
    runner.Active(false);
}