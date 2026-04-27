#pragma once
#include "Player.h"

class Game {
public:
    void run();
private:
    void createPlayer();
    void turnLoop();
    void gameOver();

    Player* player = nullptr;
    int turn = 0;
};
