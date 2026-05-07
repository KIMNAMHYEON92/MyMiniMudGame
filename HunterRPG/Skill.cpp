#include "Skill.h"
#include "Character.h"
#include "UI.h"
#include <iostream>

Skill::Skill(std::string name, Trigger trigger, int baseProbability, int priority)
    : name(name), trigger(trigger), baseProbability(baseProbability), priority(priority), isCharged(false) {}

void Skill::useSkill() {
    useCount++;
    if (useCount >= level * 5) {
        level++;
        useCount = 0;
        UI::PrintMessage("Skill Level Up! " + name + " is now level " + std::to_string(level) + "!");
    }
}

HeavyStrike::HeavyStrike() : Skill("Heavy Strike", Trigger::ON_ATTACK, 50, 1) {}

void HeavyStrike::execute(Character* caster, Character* target) {
    useSkill();
    double multiplier = 1.0 + (level - 1) * 0.1;
    double rawDamage = caster->getFinalAtk() * 1.0 + caster->getFinalSpd() * 1.0;
    int damage = target->takeDamage(rawDamage * multiplier);
    UI::PrintMessage(caster->getName() + " used " + name + " and dealt " + std::to_string(damage) + " damage!");
}

Snipe::Snipe() : Skill("Snipe", Trigger::ON_ATTACK, 30, 1) {}

void Snipe::execute(Character* caster, Character* target) {
    useSkill();
    double multiplier = 1.0 + (level - 1) * 0.1;
    double rawDamage = caster->getFinalSpd() * 3.3;
    int damage = target->takeDamage(rawDamage * multiplier);
    UI::PrintMessage(caster->getName() + " used " + name + " and dealt " + std::to_string(damage) + " damage!");
}

MagicExplosion::MagicExplosion() : Skill("Magic Explosion", Trigger::ON_ATTACK, 20, 1) {}

void MagicExplosion::execute(Character* caster, Character* target) {
    useSkill();
    double multiplier = 1.0 + (level - 1) * 0.1;
    double rawDamage = caster->getFinalAtk() * 5.0;
    int damage = target->takeDamage(rawDamage * multiplier);
    UI::PrintMessage(caster->getName() + " used " + name + " and dealt " + std::to_string(damage) + " damage!");
}

ShieldBash::ShieldBash() : Skill("Shield Bash", Trigger::ON_DEFEND, 40, 1) {}

void ShieldBash::execute(Character* caster, Character* target) {
    useSkill();
    double multiplier = 1.0 + (level - 1) * 0.1;
    double rawDamage = caster->getFinalDef() * 2.5;
    int damage = target->takeDamage(rawDamage * multiplier);
    UI::PrintMessage(caster->getName() + " triggered " + name + " and struck back for " + std::to_string(damage) + " damage!");
}

DivineGrace::DivineGrace() : Skill("Divine Grace", Trigger::ON_TURN_START, 30, 1) {}

void DivineGrace::execute(Character* caster, Character* target) {
    useSkill();
    double multiplier = 1.0 + (level - 1) * 0.1;
    int healAmount = (caster->getFinalMaxHp() * 0.25) * multiplier; // 25% heal
    caster->heal(healAmount);
    UI::PrintMessage(caster->getName() + " used " + name + " and healed for " + std::to_string(healAmount) + " HP!");
}

BasicAttack::BasicAttack() : Skill("Basic Attack", Trigger::ON_ATTACK, 100, 0) {}

void BasicAttack::useSkill() {
    // BasicAttack remains level 1 permanently
}

void BasicAttack::execute(Character* caster, Character* target) {
    int damage = target->takeDamage(caster->attack()); // 1x damage
    UI::PrintMessage(caster->getName() + " used " + name + " and dealt " + std::to_string(damage) + " damage!");
}
