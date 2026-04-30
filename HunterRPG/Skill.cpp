#include "Skill.h"
#include "Character.h"
#include <iostream>

Skill::Skill(std::string name, Trigger trigger, int baseProbability, int priority)
    : name(name), trigger(trigger), baseProbability(baseProbability), priority(priority), isCharged(false) {}

HealSkill::HealSkill() : Skill("Heal", Trigger::ON_TURN_START, 30, 1) {}

void HealSkill::execute(Character* caster, Character* target) {
    int healAmount = caster->getFinalMaxHp() * 0.2; // 20% heal
    caster->heal(healAmount);
    std::cout << caster->getName() << " used " << name << " and healed for " << healAmount << " HP!\n";
}

HeavyStrike::HeavyStrike() : Skill("Heavy Strike", Trigger::ON_ATTACK, 50, 1) {}

void HeavyStrike::execute(Character* caster, Character* target) {
    int damage = target->takeDamage(caster->attack() * 2.0); // 2.0x damage
    std::cout << caster->getName() << " used " << name << " and dealt " << damage << " damage!\n";
}

CounterAttack::CounterAttack() : Skill("Counter Attack", Trigger::ON_DEFEND, 25, 1) {}

void CounterAttack::execute(Character* caster, Character* target) {
    int damage = target->takeDamage(caster->attack()); // 1x counter attack
    std::cout << caster->getName() << " triggered " << name << " and struck back for " << damage << " damage!\n";
}

BasicAttack::BasicAttack() : Skill("Basic Attack", Trigger::ON_ATTACK, 100, 0) {}

void BasicAttack::execute(Character* caster, Character* target) {
    int damage = target->takeDamage(caster->attack()); // 1x damage
    std::cout << caster->getName() << " used " << name << " and dealt " << damage << " damage!\n";
}
