#include "EnemyShip.h"

void EnemyShip::PopulateBody() {
    body.clear();
    
    // relative points to top-left point
    std::vector<int> x_rel = {0, 0, 1, 2, 3, 3};
    std::vector<int> y_rel = {0, 1, 0, 0, 0, 1};
    
    for (int i = 0; i < x_rel.size(); i++) {
        body.push_back(SDL_Point{ref_x + x_rel[i], ref_y + y_rel[i]});
    }
}

void EnemyShip::MoveShip(Direction direction) {
    
    int x_move;
    int y_move;
    
    switch (direction) {
        case Direction::kLeft:
            x_move = -1;
            y_move =  0;
            break;
        case Direction::kRight:
            x_move = 1;
            y_move = 0;
            break;
        case Direction::kDown:
            x_move = 0;
            y_move = 1;
            break;
    }
    
    ref_x += x_move;
    ref_y += y_move;
    
    for (auto & point : body) {
        point.x += x_move;
        point.y += y_move;
    }
    
}
