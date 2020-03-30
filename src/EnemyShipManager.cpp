#include "SDL.h"

#include "EnemyShipManager.h"
#include "missile.h"

EnemyShipManager::EnemyShipManager(int gx, int gy) : grid_x(gx), grid_y(gy), engine(dev())
{
    InitializeState();
    ref_x_max = grid_x - (2*screen_buffer + cols*ship_w + ship_buffer*(cols-1));
    ref_y_max = grid_y - (2*screen_buffer + rows*ship_h + ship_buffer*(rows-1) + shooter_h);
    CreateShips();
    UpdateMissileTS();
}

void EnemyShipManager::CreateShips() {
    
    InitializeState();
    
    int ship_x;
    int ship_y;
    std::vector<EnemyShip*> thisCol;
    
    for (int col_i = 0; col_i < cols; col_i++) {
        ship_x = screen_buffer + (ship_w + ship_buffer) * col_i;
        for (int row_i = 0; row_i < rows; row_i++) {
            ship_y = screen_buffer + (ship_h + ship_buffer) * row_i;
            thisCol.push_back(new EnemyShip(ship_x,ship_y));
        }
        ships.push_back(thisCol);
        thisCol.clear();
    }
    
    UpdateMissileTS();
}

void EnemyShipManager::Update() {
    // see if ref_x and ref_y moved enough to get to the next grid
    SDL_Point prev_cell{ static_cast<int>(ref_x), static_cast<int>(ref_y)};
    UpdateRefPoint();
    SDL_Point current_cell{ static_cast<int>(ref_x), static_cast<int>(ref_y)};
    
    // move ship, and check to make sure ships all stay within the grid
    if (current_cell.x != prev_cell.x) {
        MoveShips();
        if ((current_cell.x == 0) || (current_cell.x == ref_x_max)) {
            direction = Direction::kDown;
        }
    } else if (current_cell.y != prev_cell.y) {
        MoveShips();
        if (current_cell.y == ref_y_max) {
            enemyWin = true;
        } else if (current_cell.x == 0) {
            direction = Direction::kRight;
        } else if (current_cell.x == ref_x_max) {
            direction = Direction::kLeft;
        }
    }

    // enemy ship shoot missiles
    Uint32 frame_end = SDL_GetTicks();
    
    if (frame_end - missile_ts >= missileWaitTime) {
        ShootMissile();
        UpdateMissileTS();
    }
    
    // update missiles
    if (missiles.size() > 0) {
        UpdateMissiles();
    }
    
}

void EnemyShipManager::UpdateRefPoint() {
    switch (direction) {
        case Direction::kLeft:
            ref_x -= speed;
            break;
        case Direction::kRight:
            ref_x += speed;
            break;
        case Direction::kDown:
            ref_y += speed;
            break;
    }
}

void EnemyShipManager::MoveShips() {
    for (std::vector<EnemyShip*> & col : ships) {
        for (EnemyShip* ship : col) {
            ship->moveShip(direction);
        }
    }
}

void EnemyShipManager::ShootMissile() {
    int cols_alive = ships.size(); // number of columns of ships alive
    std::uniform_int_distribution<int> distribution(0, cols_alive - 1);
    
    int col_selected = distribution(engine);
    EnemyShip* thisShip = ships[col_selected].back();
    
    int ship_x = thisShip->ref_x;
    int ship_y = thisShip->ref_y;
    
    missiles.push_back(new Missile(ship_x    , ship_y + 2, missileSpeed));
    missiles.push_back(new Missile(ship_x + 3, ship_y + 2, missileSpeed));
}

void EnemyShipManager::UpdateMissiles() {
    for (Missile *missile : missiles) {
        missile->UpdateLocation(grid_y);
    }
    
    // Clean-up missile if not active
    missiles.erase(std::remove_if(missiles.begin(),
                                  missiles.end(),
                                  [](const Missile * missile) { return !missile->active; }),
                   missiles.end());
}

int EnemyShipManager::ProcessShooterMissiles(const std::vector<Missile*> & shooterMissiles) {
    
    int shipsHit = 0;
    
    int shooterMissile_x;
    int shooterMissile_y;
     
    for (Missile *shooterMissile : shooterMissiles) {
        shooterMissile_x = static_cast<int>(shooterMissile->x);
        shooterMissile_y = static_cast<int>(shooterMissile->y);
        
        for (auto & col : ships) {
            if (!col.empty()) {
                auto & points = col.back()->body;
                for (auto & point : points) {
                    if ( (point.x == shooterMissile_x) && (point.y == shooterMissile_y) ) {
                        // ship destroyed
                        // (two missiles can't simultaneously hit the same ship)
                        shipsHit++;
                        
                        // destroy EnemyShip object that's been hit
                        col.pop_back();
                        
                        // missile no longer active
                        shooterMissile->active = false;
                        break;
                    }
                }
            }
            if (!shooterMissile->active) {
                break; // no need to look at other columns if missile already hit
            }
        }
    }
    
    // Clean-up columns if empty
    ships.erase(std::remove_if(ships.begin(),
                               ships.end(),
                               [](std::vector<EnemyShip*> col) { return col.empty(); }),
                   ships.end());
    
    return shipsHit;
}

void EnemyShipManager::UpdateMissileTS() {
    missile_ts = SDL_GetTicks();
}

void EnemyShipManager::InitializeState() {
    ref_x = 0;
    ref_y = 0;
    direction = Direction::kRight;
}
