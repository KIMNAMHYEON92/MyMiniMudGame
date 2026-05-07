#pragma once
#include "Monster.h"
#include "Player.h"

class Battle
{
private: 
    Player& player;
    Monster& monster;
public:
    Battle(Player& player, Monster& monster);
    bool run(int gateIndex, const std::vector<Monster>& monsters);
};
