#pragma once
#include <string>
#include <vector>

#include "Character.h"

using namespace std;

class Monster:public Character
{
private:
    int expReward;
    string name;
    vector<int> code;
public:
    Monster(int atk, int def, int spd, int maxHp, const string& name, int expReward);
    int getExpReward() const { return expReward;}
    string getName() const { return name; }
    vector<int> getCode() const { return code; }
    void naming();
};
