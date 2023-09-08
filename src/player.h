#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string.h>

#define MAX_NAME_LEN 20

class Player
{
public:
    Player();
    void SetScore(int point);
    void SaveToScoreBoard();
private:
    std::string name{MAX_NAME_LEN, '\0'};
    int score{0};
};

#endif /* PLAYER_H */