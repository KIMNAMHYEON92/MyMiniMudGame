#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Character.h"
#include "Job.h"

using namespace std;

class Player : public Character
{
private:
    string nick;
    std::unique_ptr<Job> currentJob;
    int exp, expToNextLevel;
    vector<int> inventory;
    
public:
    Player(int atk, int def, int spd, int maxHp, const string& nick, std::unique_ptr<Job> job);
    string getNick(){return nick;}
    string getName() const override { return nick; }
    string getCharacterClass(){return currentJob->getName();}
    std::vector<Skill*> getActiveSkills() const override { return currentJob->getSkills(); }
    int getExp(){return exp;}
    int getExpToNextLevel(){return expToNextLevel;}
    
    void gainExp(int amount);
    Stat generateLoot(int price, int bias = 0);
    void applyLoot(Stat item);
    Stat getItemStat() const { return itemStat; }
    int getScore();
};
