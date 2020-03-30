#ifndef MISSILE_H
#define MISSILE_H

class Missile {
public:
    Missile(float x, float y, float speed) : x(x), y(y), speed(speed)
    {
        
    }
    
    float x;
    float y;
    bool active{true};
    
    void UpdateLocation(const int grid_y);
    
private:
    float speed;
};

#endif
