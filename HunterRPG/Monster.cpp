#include "Monster.h"

Monster::Monster(int atk, int def, int spd, int maxHp, const string& name, int expReward)
    :Character(atk, def, spd, maxHp), name(name), expReward(expReward){}
