#pragma once

struct Stat {
    int atk;
    int def;
    int spd;
    int maxHp;
};

struct StatMultiplier {
    float atk;
    float def;
    float spd;
    float maxHp;
};

class Character
{
protected:
    Stat baseStat;
    Stat itemStat;
    StatMultiplier mult;

    int hp, level;
public:
    Character(int atk, int def, int spd, int maxHp);
    virtual ~Character(){};
    
    int getFinalAtk() const { return (int)((baseStat.atk + itemStat.atk) * mult.atk); }
    int getFinalDef() const { return (int)((baseStat.def + itemStat.def) * mult.def); }
    int getFinalSpd() const { return (int)((baseStat.spd + itemStat.spd) * mult.spd); }
    int getFinalMaxHp() const { return (int)((baseStat.maxHp + itemStat.maxHp) * mult.maxHp); }

    int getHp(){return hp;};
    int getLevel(){return level;};
    bool isAlive() const;
    virtual int takeDamage(int damage);
    virtual int attack() const;
    void levelUp();
};
