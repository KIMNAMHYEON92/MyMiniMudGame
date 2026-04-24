#pragma once

class Character
{
protected:
    int atk, def, spd;
    int hp, maxHp, level;
public:
    Character(int atk, int def, int spd, int maxHp);
    virtual ~Character(){};
    
    int getAtk(){return atk;};
    int getDef(){return def;};
    int getSpd(){return spd;};
    int getMaxHp(){return maxHp;};
    int getHp(){return hp;};
    int getLevel(){return level;};
    bool isAlive() const;
    virtual void takeDamage(int damage);
    virtual int attack() const;
    void levelUp();
};
