#ifndef MISSILE_H
#define MISSILE_H

class Missile {
public:
    // constructor
    Missile(float x, float y, float speed) : x(x), y(y), speed(speed) {}
    
    // methods
    void UpdateLocation(const int grid_y);
    
    // member variables
    float x;
    float y;
    bool active{true};
    
private:
    // private member variables
    const float speed;
};

#endif
