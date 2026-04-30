#pragma once
#include <string>
#include <vector>
#include <memory>

#include "Character.h"
#include "Skill.h"

using namespace std;

class Monster:public Character
{
private:
    int expReward;
    string name;
    vector<int> code;
    vector<unique_ptr<Skill>> skills;
    bool isElite;
public:
    Monster(int atk, int def, int spd, int maxHp, const string& name, int expReward);
    int getExpReward() const { return expReward;}
    string getName() const override { return name; }
    vector<int> getCode() const { return code; }
    void naming();
    void makeElite();
    bool getIsElite() const { return isElite; }
    vector<Skill*> getActiveSkills() const override;
};
