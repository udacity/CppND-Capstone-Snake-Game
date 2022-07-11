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
    Point start{snake.headX_,snake.headY_};
    auto distance = calculateDistance(start,food_);
    std::cout << "manhattan distance " << distance << "\n";

    // find neighbours and calculate their manhattan distance
    // => neighbours werden anhand der aktuellen Geschwindigkeit berechnet
    std::vector<RoutePlanner::Neighbour> neighbours;

    // std::vector<std::unique_ptr<RoutePlanner::Neighbour>> neighbours_new;
    // neighbours_new.emplace_back(findNeighbour_new(snake,Snake::Direction::kUp));
    // neighbours_new.emplace_back(findNeighbour_new(snake,Snake::Direction::kDown));
    // neighbours_new.emplace_back(findNeighbour_new(snake,Snake::Direction::kLeft));
    // neighbours_new.emplace_back(findNeighbour_new(snake,Snake::Direction::kRight));

 
    neighbours.emplace_back(findNeighbour(snake,Snake::Direction::kUp));
    neighbours.emplace_back(findNeighbour(snake,Snake::Direction::kDown));
    neighbours.emplace_back(findNeighbour(snake,Snake::Direction::kLeft));
    neighbours.emplace_back(findNeighbour(snake,Snake::Direction::kRight));

    std::cout << " neighbours dir ";
    printDir(neighbours[0].direction_);
    std::cout << " dist " << neighbours[0].distance_ << "\n";
    std::cout << " neighbours dir "; 
    printDir(neighbours[1].direction_);
    std::cout << " dist " << neighbours[1].distance_ << "\n";
    std::cout << " neighbours dir ";
    printDir(neighbours[2].direction_);
    std::cout << " dist " << neighbours[2].distance_ << "\n";
    std::cout << " neighbours dir ";
    printDir(neighbours[3].direction_);
    std::cout << " dist " << neighbours[3].distance_ << "\n";

    // calculate the direction of the neighbour with the shortest manhattan distance 
    std::sort(neighbours.begin(), neighbours.end(), [](RoutePlanner::Neighbour a, RoutePlanner::Neighbour b) {
        return a.distance_ < b.distance_;
    });
    
    // what would be the distance of the current direction
    float probableDistance{0.f};
    bool currentDirValid{true};
    for (const auto i : neighbours) {
        if (i.direction_ == snake.direction_) {
            probableDistance = i.distance_;
            currentDirValid = i.valid_;
            break;
        }
    }
    
    // go
    for (const auto tmp : neighbours) {
        if ((tmp.valid_) && (verifyDirection(snake,tmp.direction_))) {
            printDir(tmp.direction_);
            std::cout << "\n";
            std::cout << "current dir ";
            printDir(snake.direction_);
            std::cout << "\n";
            if ((probableDistance <= (tmp.distance_+ (snake.speed_/(snake.body_.size()!=0?snake.body_.size():1)))) && (tmp.direction_ != snake.direction_) && currentDirValid) {
                std::cout << "we keep our direction.\n";                
                controlTest(snake, snake.direction_);     
            } else {
                controlTest(snake, tmp.direction_);     
            }

            break;
        }
    }

   
    // if (distance > neighbours_[0].distance_) {
    //     controlTest(snake, neighbours[0].direction_);        
    // } else {
    //     controlTest(snake, snake.direction_);
    // }
//    std::cout << " neighbours shortest dir " << int(neighbours[0].direction_) << " dist " << neighbours[0].distance_ << "\n";

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

std::unique_ptr<RoutePlanner::Neighbour> RoutePlanner::findNeighbour_new(Snake const & snake, Snake::Direction const direction) {
    switch (direction) {
        case Snake::Direction::kLeft:
        {
            auto nbr = Point{(snake.headX_ - snake.speed_) <= 0.0f ? 32.0F: (snake.headX_ - snake.speed_) ,snake.headY_};
            return std::make_unique<RoutePlanner::Neighbour>(calculateDistance(nbr,food_),Snake::Direction::kLeft);
        }
        break;
        case Snake::Direction::kRight:
        {
            auto nbr =  Point{(snake.headX_ + snake.speed_) >= 32.0f ? 0.0F: (snake.headX_ + snake.speed_) ,snake.headY_};
            return std::make_unique<RoutePlanner::Neighbour>(calculateDistance(nbr,food_),Snake::Direction::kRight);
        }
        break;
        case Snake::Direction::kUp:
        {
            auto nbr =  Point{snake.headX_,(snake.headY_ - snake.speed_) <= 0.0f ? 32.0F: (snake.headY_ - snake.speed_)};
            return std::make_unique<RoutePlanner::Neighbour>(calculateDistance(nbr,food_),Snake::Direction::kUp);
        }
        break;
        case Snake::Direction::kDown:
        {
            auto nbr =  Point{snake.headX_,(snake.headY_ + snake.speed_) >= 32.0f ? 0.0F: (snake.headY_ + snake.speed_)};
            return std::make_unique<RoutePlanner::Neighbour>(calculateDistance(nbr,food_),Snake::Direction::kDown);
        }
        break;
    }

    auto start = Point{snake.headX_,snake.headY_};
    
    return std::make_unique<RoutePlanner::Neighbour>(calculateDistance(start,food_),Snake::Direction::kUp);
}

RoutePlanner::Neighbour RoutePlanner::findNeighbour(Snake const & snake, Snake::Direction const direction) {
    switch (direction) {
        case Snake::Direction::kLeft:
        {
            auto nbr = Point{(snake.headX_ - snake.speed_) <= 0.0f ? 32.0F: (snake.headX_ - snake.speed_) ,snake.headY_};
            auto valid = verifyNeighbours(snake,nbr);
            if (!verifyNeighbours(snake,nbr)) {
                std::cout << "LEFT neighbour will touch body\n";
            }
            return Neighbour{calculateDistance(nbr,food_),Snake::Direction::kLeft,valid};
        }
        break;
        case Snake::Direction::kRight:
        {
            auto nbr =  Point{(snake.headX_ + snake.speed_) >= 32.0f ? 0.0F: (snake.headX_ + snake.speed_) ,snake.headY_};
            auto valid = verifyNeighbours(snake,nbr);
            if (! verifyNeighbours(snake,nbr)) {
                std::cout << "RIGHT neighbour will touch body\n";
            }
            return Neighbour{calculateDistance(nbr,food_),Snake::Direction::kRight,valid};
        }
        break;
        case Snake::Direction::kUp:
        {
            auto nbr =  Point{snake.headX_,(snake.headY_ - snake.speed_) <= 0.0f ? 32.0F: (snake.headY_ - snake.speed_)};
            auto valid = verifyNeighbours(snake,nbr);
            if (!verifyNeighbours(snake,nbr)) {
                std::cout << "UP neighbour will touch body\n";
            }
            return Neighbour{calculateDistance(nbr,food_),Snake::Direction::kUp,valid};
        }
        break;
        case Snake::Direction::kDown:
        {
            auto nbr =  Point{snake.headX_,(snake.headY_ + snake.speed_) >= 32.0f ? 0.0F: (snake.headY_ + snake.speed_)};
            auto valid = verifyNeighbours(snake,nbr);
            if (!verifyNeighbours(snake,nbr)) {
                std::cout << "DOWN neighbour will touch body\n";
            }
            return Neighbour{calculateDistance(nbr,food_),Snake::Direction::kDown,valid};
        }
        break;
    }

    auto start = Point{snake.headX_,snake.headY_};
    
    return Neighbour{calculateDistance(start,food_),Snake::Direction::kUp};
}

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