#ifndef MISSILE_H
#define MISSILE_H

class Missile {
public:
    Missile(float x, float y, float speed, int grid_y) : x(x), y(y), speed(speed), grid_y(grid_y)
    {
        
    }
    
    float x;
    float y;
    int grid_y;
    bool active{true};
    
    void UpdateLocation();
    
private:
    float speed;
};

#endif
