#include "Skill.h"
#include "Character.h"
#include <iostream>

Skill::Skill(std::string name, Trigger trigger, int baseProbability)
    : name(name), trigger(trigger), baseProbability(baseProbability), isCharged(false) {}

HealSkill::HealSkill() : Skill("Heal", Trigger::ON_TURN_START, 30) {}

void HealSkill::execute(Character* caster, Character* target) {
    int healAmount = caster->getFinalMaxHp() * 0.2; // 20% heal
    caster->heal(healAmount);
    std::cout << caster->getName() << " used " << name << " and healed for " << healAmount << " HP!\n";
}

HeavyStrike::HeavyStrike() : Skill("Heavy Strike", Trigger::ON_ATTACK, 40) {}

void HeavyStrike::execute(Character* caster, Character* target) {
    int damage = target->takeDamage(caster->attack() * 1.5); // 1.5x damage
    std::cout << caster->getName() << " used " << name << " and dealt " << damage << " damage!\n";
}

CounterAttack::CounterAttack() : Skill("Counter Attack", Trigger::ON_DEFEND, 25) {}

void CounterAttack::execute(Character* caster, Character* target) {
    int damage = target->takeDamage(caster->attack()); // 1x counter attack
    std::cout << caster->getName() << " triggered " << name << " and struck back for " << damage << " damage!\n";
}
