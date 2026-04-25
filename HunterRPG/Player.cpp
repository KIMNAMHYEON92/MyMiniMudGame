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
    vector<int> newItem={0,0,0,0};
    vector<int> change={0,0,0,0};
    int input;
    int rank = price *4;
    for (int i=0;i<rank;i++)
    {
        int stat = rand()%4;
        newItem[stat]++;        
    }
    for (int i=0;i<4;i++)
    {
        change[i]=newItem[i]-inventory[i];
    }
    cout << "New item dropped!" << "\n";
    cout << "RANK : " << price << ")\n";
    cout << "ATK + " << newItem[0] << " (" << change[0] << ")\n";
    cout << "DEF + " << newItem[1] << " (" << change[1] << ")\n";
    cout << "SPD + " << newItem[2] << " (" << change[2] << ")\n";
    cout << "MAX HP + " << (10*newItem[3]) << " (" << (10*change[3]) << ")\n";
    cout << "Want to replace?" << "\n";
    cout << "1: Yes, 2: No, Input:";
    cin >> input;
    switch (input)
    {
    case 1:
        atk+=change[0];
        def+=change[1];
        spd+=change[2];
        maxHp+=10*change[3];
        inventory=newItem;
        break;
    default:
        break;
    }
    system("cls");
    cout << nick << "'s status" << "\n";
    cout << "Level: " << level << "\n";
    cout << "HP: " << hp << " / " << maxHp << "\n";
    cout << "ATK: " << atk << "\n";
    cout << "DEF: " << def << "\n";
    cout << "SPD: " << spd << "\n";
    system("pause");
    
}
int Player::getScore()
{
    return atk+def+spd+(maxHp/10)+level;
}