#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Character.h" // We will define StatMultiplier in Character.h
#include "Skill.h"

class Job {
protected:
    std::vector<std::unique_ptr<Skill>> skills;
public:
    virtual ~Job() = default;
    virtual std::string getName() const = 0;
    virtual StatMultiplier getMultiplier() const = 0;
    std::vector<Skill*> getSkills() const {
        std::vector<Skill*> rawSkills;
        for (const auto& skill : skills) {
            rawSkills.push_back(skill.get());
        }
        return rawSkills;
    }
};

class MeleeDealer : public Job {
public:
    MeleeDealer() {
        skills.push_back(std::make_unique<BasicAttack>());
        skills.push_back(std::make_unique<HeavyStrike>());
    }
    std::string getName() const override { return "MeleeDealer"; }
    StatMultiplier getMultiplier() const override { return {1.2f, 1.1f, 1.0f, 1.2f}; }
};

class RangeDealer : public Job {
public:
    RangeDealer() {
        skills.push_back(std::make_unique<BasicAttack>());
        skills.push_back(std::make_unique<Snipe>());
    }
    std::string getName() const override { return "RangeDealer"; }
    StatMultiplier getMultiplier() const override { return {1.3f, 0.9f, 1.2f, 1.0f}; }
};

class SpellDealer : public Job {
public:
    SpellDealer() {
        skills.push_back(std::make_unique<BasicAttack>());
        skills.push_back(std::make_unique<MagicExplosion>());
    }
    std::string getName() const override { return "SpellDealer"; }
    StatMultiplier getMultiplier() const override { return {1.5f, 0.8f, 1.1f, 0.9f}; }
};

class Tanker : public Job {
public:
    Tanker() {
        skills.push_back(std::make_unique<BasicAttack>());
        skills.push_back(std::make_unique<ShieldBash>());
    }
    std::string getName() const override { return "Tanker"; }
    StatMultiplier getMultiplier() const override { return {0.9f, 1.5f, 0.8f, 1.5f}; }
};

class Healer : public Job {
public:
    Healer() {
        skills.push_back(std::make_unique<BasicAttack>());
        skills.push_back(std::make_unique<DivineGrace>());
    }
    std::string getName() const override { return "Healer"; }
    StatMultiplier getMultiplier() const override { return {1.0f, 1.1f, 1.0f, 1.1f}; }
};

class NoneJob : public Job {
public:
    NoneJob() {
        skills.push_back(std::make_unique<BasicAttack>());
    }
    std::string getName() const override { return "None"; }
    StatMultiplier getMultiplier() const override { return {1.0f, 1.0f, 1.0f, 1.0f}; }
};
