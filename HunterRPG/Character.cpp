#include "Character.h"

Character::Character(int atk, int def, int spd, int maxHp)
    : atk(atk), def(def), spd(spd), maxHp(maxHp)
{
    level=0;
    hp = maxHp;
}
bool Character::isAlive() const
{
    return hp>0;
}
void Character::takeDamage(int damage)
{
    if (damage>0)
    {
        hp -= damage;
    }
    else
    {
        hp -= 1;
    }
    if (hp < 0) hp = 0;
}
int Character::attack() const
{
    return atk;
}

void Character::levelUp()
{
    level++;
}
