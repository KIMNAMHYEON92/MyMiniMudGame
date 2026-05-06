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
    int level = 1;
    int useCount = 0;

    Skill(std::string name, Trigger trigger, int baseProbability, int priority = 0);
    virtual ~Skill() = default;

    virtual void useSkill();
    virtual void execute(Character* caster, Character* target) = 0;
};

class HeavyStrike : public Skill {
public:
    HeavyStrike();
    void execute(Character* caster, Character* target) override;
};

class Snipe : public Skill {
public:
    Snipe();
    void execute(Character* caster, Character* target) override;
};

class MagicExplosion : public Skill {
public:
    MagicExplosion();
    void execute(Character* caster, Character* target) override;
};

class ShieldBash : public Skill {
public:
    ShieldBash();
    void execute(Character* caster, Character* target) override;
};

class DivineGrace : public Skill {
public:
    DivineGrace();
    void execute(Character* caster, Character* target) override;
};

class BasicAttack : public Skill {
public:
    BasicAttack();
    void useSkill() override;
    void execute(Character* caster, Character* target) override;
};
