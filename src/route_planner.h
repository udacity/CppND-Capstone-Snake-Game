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
        Neighbour(float const dist, Snake::Direction const direction) : distance_(dist),direction_(direction),valid_(true) {}
        Neighbour(float const dist, Snake::Direction const direction,bool valid) : distance_(dist),direction_(direction),valid_(valid) {}
        float distance_;
        Snake::Direction direction_;
        bool valid_;
    };

    void run(Snake & snake);

    void updateFood(SDL_Point const & food);

private:
    float calculateDistance(Point const & start, Point const & destination);
    Neighbour findNeighbour(Snake const & snake, Snake::Direction const direction);
    std::unique_ptr<RoutePlanner::Neighbour> findNeighbour_new(Snake const & snake, Snake::Direction const direction);
    bool verifyDirection(Snake & snake,  Snake::Direction const & input);
    void controlTest(Snake & snake, Snake::Direction const & input);
    bool verifyNeighbours(Snake const & snake, Point const & neighbour);
    Point food_{0.f,0.f};

    std::vector<Neighbour> neighbours_;

};

}

#endif