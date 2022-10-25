#include "route_planner.h"

#include "snake.h"

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <memory.h>

namespace SnakeGame {

void RoutePlanner::run(Snake * snake,SDL_Point const & food) {

    updateFood(food);
    // calculate manhattandistance from snake head to food
    const Point start{snake->headX_,snake->headY_};
    const auto distance = calculateDistance(start,food_);

    // find neighbours and calculate their manhattan distance
    neighbours_.clear();

    addNeighbours(snake);

    const auto probableWinner = std::find_if(neighbours_.cbegin(),neighbours_.cend(), 
                            [&](std::unique_ptr<RoutePlanner::Neighbour> const & neighbour) {return verifyDirection(snake,neighbour->direction_);});
    
    if (neighbours_.end() != probableWinner) {

        const auto probableNeighbourIntheSameDirection = std::find_if(neighbours_.cbegin(),neighbours_.cend(), 
                                [&](std::unique_ptr<RoutePlanner::Neighbour> const & neighbour) {return neighbour->direction_ == snake->direction_;});

        if (neighbours_.end() != probableNeighbourIntheSameDirection) {
            // add some salt
            const auto distance = (*probableWinner)->distance_ + (snake->speed_/(snake->body_.size()!=0?snake->body_.size():1));
            if ( ((*probableNeighbourIntheSameDirection)->distance_ <= distance) && ((*probableWinner)->direction_ != snake->direction_) ) {
                // std::cout << "we keep our direction.\n";                
                controlTest(snake, snake->direction_);     
            } else {
                // 
                controlTest(snake, (*probableWinner)->direction_);     
            }
        } else {
            // std::cout << "no same direction\n";
            controlTest(snake, (*probableWinner)->direction_);     
        }
    } else {
        // std::cout << "no winner\n";
    }

}

void RoutePlanner::controlTest(Snake * snake, Direction const & input) {
    switch (input) 
    {
        case Direction::kUp:
          snake->ChangeDirection(Direction::kUp,
                          Direction::kDown);
        break;
        case Direction::kDown:
          snake->ChangeDirection(Direction::kDown,
                          Direction::kUp);
        break;
        case Direction::kLeft:
          snake->ChangeDirection(Direction::kLeft,
                          Direction::kRight);
        break;
        case Direction::kRight:
          snake->ChangeDirection(Direction::kRight,
                          Direction::kLeft);
        break;
        case Direction::kQuit:
        break;
    };
}

bool RoutePlanner::verifyDirection(Snake * snake,   Direction const & input) {
    switch (input) 
    {
        case  Direction::kUp:
            if (snake->direction_ ==  Direction::kDown)
                return false;
        break;
        case  Direction::kDown:
            if (snake->direction_ ==  Direction::kUp)
                return false;
        break;
        case  Direction::kLeft:
            if (snake->direction_ ==  Direction::kRight)
                return false;
        break;
        case  Direction::kRight:
            if (snake->direction_ ==  Direction::kLeft)
                return false;
        break;
        case Direction::kQuit:
            return false;
    };
    return true;    
}

void RoutePlanner::addNeighbours(Snake const * snake) {

    // lets find neighbours in all direction    
    findNeighbour(snake, Direction::kUp);
    findNeighbour(snake, Direction::kDown);
    findNeighbour(snake, Direction::kLeft);
    findNeighbour(snake, Direction::kRight);

    // what happens if we don't find any..
    // nothing we will continue in the same direction - we might die ...

    // calculate the direction of the neighbour with the shortest manhattan distance 
    std::sort(neighbours_.begin(), neighbours_.end(), [](std::unique_ptr<RoutePlanner::Neighbour> & a, std::unique_ptr<RoutePlanner::Neighbour> &b) {
        return a->distance_ < b->distance_;
    });

}
//std::unique_ptr<RoutePlanner::Neighbour> RoutePlanner::findNeighbour(Snake const & snake,  Direction const direction) {
void RoutePlanner::findNeighbour(Snake const * snake,  Direction const direction) {
    switch (direction) {
        case  Direction::kLeft:
        {
            auto neighbour = Point{(snake->headX_ - snake->speed_) <= 0.0f ? 32.0F: (snake->headX_ - snake->speed_) ,snake->headY_};
            if (verifyNeighbours(snake,neighbour)) {
                 neighbours_.emplace_back(std::make_unique<RoutePlanner::Neighbour>(calculateDistance(neighbour,food_), Direction::kLeft));
            }
        }
        break;
        case  Direction::kRight:
        {
            auto neighbour =  Point{(snake->headX_ + snake->speed_) >= 32.0f ? 0.0F: (snake->headX_ + snake->speed_) ,snake->headY_};
            if (verifyNeighbours(snake,neighbour)) {
                 neighbours_.emplace_back(std::make_unique<RoutePlanner::Neighbour>(calculateDistance(neighbour,food_), Direction::kRight));
            }
        }
        break;
        case  Direction::kUp:
        {
            auto neighbour =  Point{snake->headX_,(snake->headY_ - snake->speed_) <= 0.0f ? 32.0F: (snake->headY_ - snake->speed_)};
            if (verifyNeighbours(snake,neighbour)) {
                 neighbours_.emplace_back(std::make_unique<RoutePlanner::Neighbour>(calculateDistance(neighbour,food_), Direction::kUp));
            }
        }
        break;
        case  Direction::kDown:
        {
            auto neighbour =  Point{snake->headX_,(snake->headY_ + snake->speed_) >= 32.0f ? 0.0F: (snake->headY_ + snake->speed_)};
            if (verifyNeighbours(snake,neighbour)) {
                 neighbours_.emplace_back(std::make_unique<RoutePlanner::Neighbour>(calculateDistance(neighbour,food_), Direction::kDown));
            }
        }
        break;
        case Direction::kQuit:
        break;
    }
}

// verification if neighbour would touch body
bool RoutePlanner::verifyNeighbours(Snake const * snake, Point const & neighbour) {
    auto checkIsValid = [&](std::unique_ptr<SDL_Point> const &point) {
        return ( (static_cast<int>(neighbour.x_) == point->x) && 
                 (static_cast<int>(neighbour.y_) == point->y) );
    };
    return std::none_of(snake->body_.cbegin(), snake->body_.cend(), checkIsValid); 
}

void RoutePlanner::updateFood(SDL_Point const & food) {
    food_.x_ = static_cast<float>(food.x);
    food_.y_ = static_cast<float>(food.y);
}


float RoutePlanner::calculateDistance(Point const & start, Point const & destination) {
    return std::sqrt(std::pow((start.x_ - destination.x_), 2) + std::pow((start.y_ - destination.y_), 2));    
}

}