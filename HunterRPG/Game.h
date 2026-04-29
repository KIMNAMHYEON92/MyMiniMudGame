#pragma once
#include "Player.h"
#include <memory>
#include <vector>

class Game {
public:
    void run();
private:
    int irand(int min,int max);
    void createPlayer();
    void turnLoop();
    void gameOver();

    std::unique_ptr<Player> player;
    std::vector<Stat> lootBox;
    int turn = 0;
};
