#ifndef ROUTE_PLANNER_H
#define ROUTE_PLANNER_H
#include "SDL.h"
#include "snake.h"

#include <memory>
namespace SnakeGame {


class RoutePlanner {
public:
    RoutePlanner() = default;
    ~RoutePlanner() = default;
    RoutePlanner(RoutePlanner const & other ) = delete;
    RoutePlanner(RoutePlanner  && other ) = delete;
    RoutePlanner& operator=(RoutePlanner const & other ) = delete;
    RoutePlanner& operator=(RoutePlanner  && other ) = delete;
    
    struct Point {
        float x_;
        float y_;
    };

    struct Neighbour {
        Neighbour(float const dist, Direction const direction) : distance_(dist),direction_(direction) {}
        float distance_;
        Direction direction_;
    };

    void run(Snake * snake, SDL_Point const & food);
    void updateFood(SDL_Point const & food);

private:
    float calculateDistance(Point const & start, Point const & destination);
    void findNeighbour(Snake const * snake, Direction const direction);
    bool verifyDirection(Snake * snake,  Direction const & input);
    void controlTest(Snake * snake, Direction const & input);
    bool verifyNeighbours(Snake const * snake, Point const & neighbour);
    void addNeighbours(Snake const * snake);
    
    Point food_{0.f,0.f};

    std::vector<std::unique_ptr<RoutePlanner::Neighbour>> neighbours_{};

};

}

#endif