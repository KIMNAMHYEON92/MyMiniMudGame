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

#include <string>
#include <vector>

class Skill;

class Character
{
protected:
    Stat baseStat;
    Stat itemStat;
    Stat buffStat;
    StatMultiplier mult;
    StatMultiplier buffMult;

    int hp, level, luck;
public:
    Character(int atk, int def, int spd, int maxHp);
    virtual ~Character(){};
    
    int getFinalAtk() const { return (int)((baseStat.atk + itemStat.atk + buffStat.atk) * mult.atk * buffMult.atk); }
    int getFinalDef() const { return (int)((baseStat.def + itemStat.def + buffStat.def) * mult.def * buffMult.def); }
    int getFinalSpd() const { return (int)((baseStat.spd + itemStat.spd + buffStat.spd) * mult.spd * buffMult.spd); }
    int getFinalMaxHp() const { return (int)((baseStat.maxHp + itemStat.maxHp + buffStat.maxHp) * mult.maxHp * buffMult.maxHp); }

    int getHp(){return hp;};
    int getLevel(){return level;};
    int getLuck() const { return luck; }
    void setLuck(int newLuck) { luck = newLuck; }
    void resetBuffs();
    bool isAlive() const;
    virtual int takeDamage(int damage);
    virtual int attack() const;
    void levelUp();
    void heal(int amount);
    virtual std::string getName() const = 0;
    virtual std::vector<Skill*> getActiveSkills() const { return {}; }
};
