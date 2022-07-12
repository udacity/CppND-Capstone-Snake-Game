#include "route_planner.h"

#include "snake.h"


#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <memory.h>

namespace SnakeGame {

void printDir(Snake::Direction const & input) {
    switch (input) 
    {
        case Snake::Direction::kUp:
            std::cout << "  oben";
        break;
        case Snake::Direction::kDown:
            std::cout << "  unten";
        break;
        case Snake::Direction::kLeft:
            std::cout << "  links";
        break;
        case Snake::Direction::kRight:
            std::cout << "  rechts";
        break;
    };

}

void RoutePlanner::run(Snake & snake) {
    // get food coordinates
    std::cout << " food_.x " << food_.x_ << " food_.y " << food_.y_ << "\n";

    // get snake head coordinates
    std::cout << " head.x " << snake.headX_ << " head.y " << snake.headY_ << " gridHeight_ " << snake.gridHeight_ << "  gridWidth_ " << snake.gridWidth_ << "\n";

    // calculate manhattandistance from snake head to food
    const Point start{snake.headX_,snake.headY_};
    const auto distance = calculateDistance(start,food_);
    std::cout << "manhattan distance " << distance << "\n";

    // find neighbours and calculate their manhattan distance
    neighbours_.clear();

    addNeighbours(snake);

    const auto probableWinner = std::find_if(neighbours_.cbegin(),neighbours_.cend(), 
                            [&](std::unique_ptr<RoutePlanner::Neighbour> const & neighbour) {return verifyDirection(snake,neighbour->direction_);});
    
    if (neighbours_.end() != probableWinner) {

        const auto probableNeighbourIntheSameDirection = std::find_if(neighbours_.cbegin(),neighbours_.cend(), 
                                [&](std::unique_ptr<RoutePlanner::Neighbour> const & neighbour) {return neighbour->direction_ == snake.direction_;});

        if (neighbours_.end() != probableNeighbourIntheSameDirection) {
            // add some salt
            const auto distance = (*probableWinner)->distance_ + (snake.speed_/(snake.body_.size()!=0?snake.body_.size():1));
            if ( ((*probableNeighbourIntheSameDirection)->distance_ <= distance) && ((*probableWinner)->direction_ != snake.direction_) ) {
                std::cout << "we keep our direction.\n";                
                controlTest(snake, snake.direction_);     
            } else {
                std::cout << " winner direction ";
                printDir((*probableWinner)->direction_);
                std::cout << "\n";
                controlTest(snake, (*probableWinner)->direction_);     
            }
        } else {
            std::cout << "no same direction\n";
            controlTest(snake, (*probableWinner)->direction_);     
        }
    } else {
        std::cout << "no winner\n";
    }

}

void RoutePlanner::controlTest(Snake & snake, Snake::Direction const & input) {
    switch (input) 
    {
        case Snake::Direction::kUp:
          snake.ChangeDirection(Snake::Direction::kUp,
                          Snake::Direction::kDown);
        break;
        case Snake::Direction::kDown:
          snake.ChangeDirection(Snake::Direction::kDown,
                          Snake::Direction::kUp);
        break;
        case Snake::Direction::kLeft:
          snake.ChangeDirection(Snake::Direction::kLeft,
                          Snake::Direction::kRight);
        break;
        case Snake::Direction::kRight:
          snake.ChangeDirection(Snake::Direction::kRight,
                          Snake::Direction::kLeft);
        break;
    };
}
bool RoutePlanner::verifyDirection(Snake & snake,  Snake::Direction const & input) {
    switch (input) 
    {
        case Snake::Direction::kUp:
            if (snake.direction_ == Snake::Direction::kDown)
                return false;
        break;
        case Snake::Direction::kDown:
            if (snake.direction_ == Snake::Direction::kUp)
                return false;
        break;
        case Snake::Direction::kLeft:
            if (snake.direction_ == Snake::Direction::kRight)
                return false;
        break;
        case Snake::Direction::kRight:
            if (snake.direction_ == Snake::Direction::kLeft)
                return false;
        break;
    };
    return true;    
}

void RoutePlanner::addNeighbours(Snake const & snake) {

    // lets find neighbours in all direction    
    findNeighbour(snake,Snake::Direction::kUp);
    findNeighbour(snake,Snake::Direction::kDown);
    findNeighbour(snake,Snake::Direction::kLeft);
    findNeighbour(snake,Snake::Direction::kRight);

    // what happens if we don't find any..
    // nothing we will continue in the same direction - we might die ...

    // calculate the direction of the neighbour with the shortest manhattan distance 
    std::sort(neighbours_.begin(), neighbours_.end(), [](std::unique_ptr<RoutePlanner::Neighbour> & a, std::unique_ptr<RoutePlanner::Neighbour> &b) {
        return a->distance_ < b->distance_;
    });

}
//std::unique_ptr<RoutePlanner::Neighbour> RoutePlanner::findNeighbour(Snake const & snake, Snake::Direction const direction) {
void RoutePlanner::findNeighbour(Snake const & snake, Snake::Direction const direction) {
    switch (direction) {
        case Snake::Direction::kLeft:
        {
            auto neighbour = Point{(snake.headX_ - snake.speed_) <= 0.0f ? 32.0F: (snake.headX_ - snake.speed_) ,snake.headY_};
            if (verifyNeighbours(snake,neighbour)) {
                 neighbours_.emplace_back(std::make_unique<RoutePlanner::Neighbour>(calculateDistance(neighbour,food_),Snake::Direction::kLeft));
            }
        }
        break;
        case Snake::Direction::kRight:
        {
            auto neighbour =  Point{(snake.headX_ + snake.speed_) >= 32.0f ? 0.0F: (snake.headX_ + snake.speed_) ,snake.headY_};
            if (verifyNeighbours(snake,neighbour)) {
                 neighbours_.emplace_back(std::make_unique<RoutePlanner::Neighbour>(calculateDistance(neighbour,food_),Snake::Direction::kRight));
            }
        }
        break;
        case Snake::Direction::kUp:
        {
            auto neighbour =  Point{snake.headX_,(snake.headY_ - snake.speed_) <= 0.0f ? 32.0F: (snake.headY_ - snake.speed_)};
            if (verifyNeighbours(snake,neighbour)) {
                 neighbours_.emplace_back(std::make_unique<RoutePlanner::Neighbour>(calculateDistance(neighbour,food_),Snake::Direction::kUp));
            }
        }
        break;
        case Snake::Direction::kDown:
        {
            auto neighbour =  Point{snake.headX_,(snake.headY_ + snake.speed_) >= 32.0f ? 0.0F: (snake.headY_ + snake.speed_)};
            if (verifyNeighbours(snake,neighbour)) {
                 neighbours_.emplace_back(std::make_unique<RoutePlanner::Neighbour>(calculateDistance(neighbour,food_),Snake::Direction::kDown));
            }
        }
        break;
    }
}

// verification if neighbour would touch body
bool RoutePlanner::verifyNeighbours(Snake const & snake, Point const & neighbour) {

    bool isValid{true};
    auto checkIsValid = [&](std::unique_ptr<SDL_Point> const &point) {
        if ( (static_cast<int>(neighbour.x_) == point->x) && 
            (static_cast<int>(neighbour.y_) == point->y) )
        {   
            isValid = false;
        }
    };
    // Check if the snake has died.
    std::for_each(snake.body_.cbegin(), snake.body_.cend(), checkIsValid); 
    return isValid;
}

void RoutePlanner::updateFood(SDL_Point const & food) {
    food_.x_ = static_cast<float>(food.x);
    food_.y_ = static_cast<float>(food.y);
}


float RoutePlanner::calculateDistance(Point const & start, Point const & destination) {
    return std::sqrt(std::pow((start.x_ - destination.x_), 2) + std::pow((start.y_ - destination.y_), 2));    
}

}