#include "Player.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

Player::Player(int atk, int def, int spd, int maxHp, const string& nick, std::unique_ptr<Job> job)
    : Character(atk, def, spd, maxHp), nick(nick), currentJob(std::move(job))
{
    mult = currentJob->getMultiplier();
    hp = getFinalMaxHp(); // apply multiplier to max hp and init hp

    exp=0;
    expToNextLevel=level*10;
    inventory={0,0,0,0};
}
void Player::gainExp(int amount){
    exp+=amount;
    if (exp>expToNextLevel)
    {
        cout << "\nLevel UP!\n";
        exp-=expToNextLevel;
        levelUp();
        srand((unsigned int)time(NULL));
        for (int i=0;i<4;i++)
        {
            int stat = rand()%4;
            switch (stat)
            {
            case 0:
                baseStat.atk+=10;
                cout << "ATK +10\n";
                break;
            case 1:
                baseStat.def+=10;
                cout << "DEF +10\n";
                break;
            case 2:
                baseStat.spd+=10;
                cout << "SPD +10\n";
                break;
            case 3:
                baseStat.maxHp+=100;
                cout << "MAXHP +100\n";
                break;
            default:break;
            }
        }
        cout << "\n";
        hp=getFinalMaxHp();
        expToNextLevel=level*10;
        cout << "(exp: " << exp << " / " << expToNextLevel << ")\n";
        system("pause");
    }
    else
    {        
        cout << "exp +" << amount << ", (exp: " << exp << " / " << expToNextLevel << ")\n";
    }
}
Stat Player::generateLoot(int price){
    srand((unsigned int)time(NULL));
    Stat newItem = {0, 0, 0, 0};
    int rank = price * 4;
    for (int i = 0; i < rank; i++)
    {
        int stat = rand() % 4;
        switch (stat) {
            case 0: newItem.atk += 10; break;
            case 1: newItem.def += 10; break;
            case 2: newItem.spd += 10; break;
            case 3: newItem.maxHp += 100; break;
        }
    }
    return newItem;
}

void Player::applyLoot(Stat item){
    itemStat = item;
    // Keep HP within the new max HP
    if (hp > getFinalMaxHp()) {
        hp = getFinalMaxHp();
    }
}

int Player::getScore()
{
    return getFinalAtk()+getFinalDef()+getFinalSpd()+(getFinalMaxHp()/10)+level;
}