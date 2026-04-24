#pragma once
#include <string>
#include <vector>
#include "Character.h"'

using namespace std;

class Player : public Character
{
private:
    string nick;
    string characterClass;
    int exp, expToNextLevel;
    vector<int> inventory;
    
public:
    Player(int atk, int def, int spd, int maxHp, const string& nick, const string& characterClass);
    string getNick(){return nick;}
    string getCharacterClass(){return characterClass;}
    int getExp(){return exp;}
    int getExpToNextLevel(){return expToNextLevel;}
    
    void gainExp(int amount);
    void Loot(int price = 1);
};
