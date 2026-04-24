#include "Player.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

Player::Player(int atk, int def, int spd, int maxHp, const string& nick, const string& characterClass)
    : Character(atk, def, spd, maxHp), nick(nick), characterClass(characterClass)
{
    exp=0;
    expToNextLevel=level*10;
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
        cout << "(exp: " << exp << " / " << expToNextLevel << ")\n";
        system("pause");
    }
    else
    {        
        cout << "exp +" << amount << ", (exp: " << exp << " / " << expToNextLevel << ")\n";
    }
}
void Player::Loot(int price){
    srand((unsigned int)time(NULL));
    
}
int Player::getScore()
{
    return atk+def+spd+(maxHp/10)+level;
}