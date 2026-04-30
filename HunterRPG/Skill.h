#pragma once

#include <string>

class Character;

enum class Trigger { ON_TURN_START, ON_ATTACK, ON_DEFEND };

class Skill {
public:
    std::string name;
    Trigger trigger;
    int baseProbability;
    int priority;
    bool isCharged;

    Skill(std::string name, Trigger trigger, int baseProbability, int priority = 0);
    virtual ~Skill() = default;

    virtual void execute(Character* caster, Character* target) = 0;
};

class HealSkill : public Skill {
public:
    HealSkill();
    void execute(Character* caster, Character* target) override;
};

class HeavyStrike : public Skill {
public:
    HeavyStrike();
    void execute(Character* caster, Character* target) override;
};

class CounterAttack : public Skill {
public:
    CounterAttack();
    void execute(Character* caster, Character* target) override;
};

class BasicAttack : public Skill {
public:
    BasicAttack();
    void execute(Character* caster, Character* target) override;
};
