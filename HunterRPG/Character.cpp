#include "Character.h"

Character::Character(int atk, int def, int spd, int maxHp)
{
    baseStat = {atk, def, spd, maxHp};
    itemStat = {0, 0, 0, 0};
    buffStat = {0, 0, 0, 0};
    mult = {1.0f, 1.0f, 1.0f, 1.0f};
    buffMult = {1.0f, 1.0f, 1.0f, 1.0f};

    level=0;
    hp = getFinalMaxHp();
    luck = 0;
}

void Character::resetBuffs()
{
    buffStat = {0, 0, 0, 0};
    buffMult = {1.0f, 1.0f, 1.0f, 1.0f};
}
bool Character::isAlive() const
{
    return hp>0;
}
int Character::takeDamage(int rawDamage)
{
    int damage = (int)(rawDamage * (100.0 / (100.0 + getFinalDef())));
    if (damage < 1) damage = 1;

    hp -= damage;
    if (hp < 0) hp = 0;
    return damage;
}
int Character::attack() const
{
    return getFinalAtk();
}

void Character::levelUp()
{
    level++;
}

void Character::heal(int amount)
{
    hp += amount;
    if (hp > getFinalMaxHp()) {
        hp = getFinalMaxHp();
    }
}
