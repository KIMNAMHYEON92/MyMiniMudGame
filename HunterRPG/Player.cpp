#include "Player.h"
#include <ctime>
#include <iostream>

Player::Player(int atk, int def, int spd, int maxHp, const string& nick, const string& characterClass)
    : Character(atk, def, spd, maxHp), nick(nick), characterClass(characterClass)
{
    exp=0;
    expToNextLevel=level*10;
}
void Player::gainExp(int amount){
    exp+=amount;
    if (exp>=expToNextLevel)
    {
        cout << "Level UP!\n";
        exp-=expToNextLevel;
        levelUp();
        srand((unsigned int)time(NULL));
        for (int i=0;i<4;i++)
        {
            switch (rand()%4)
            {
            case 0:
                atk++;
                cout << "ATK +1\n";
                break;
            case 1:
                def++;
                cout << "DEF +1\n";
                break;
            case 2:
                spd++;
                cout << "SPD +1\n";
                break;
            case 3:
                maxHp+=10;
                cout << "MAXHP +10\n";
                break;
            default:break;
            }
        }
        cout << "\n";
        hp=maxHp;
        expToNextLevel=level*10;
    }
}
void Player::Loot(int price){
    srand((unsigned int)time(NULL));
    
}