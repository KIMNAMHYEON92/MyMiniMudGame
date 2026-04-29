#pragma once
#include <string>
#include "Character.h" // We will define StatMultiplier in Character.h

class Job {
public:
    virtual ~Job() = default;
    virtual std::string getName() const = 0;
    virtual StatMultiplier getMultiplier() const = 0;
};

class MeleeDealer : public Job {
public:
    std::string getName() const override { return "MeleeDealer"; }
    StatMultiplier getMultiplier() const override { return {1.2f, 1.1f, 1.0f, 1.2f}; }
};

class RangeDealer : public Job {
public:
    std::string getName() const override { return "RangeDealer"; }
    StatMultiplier getMultiplier() const override { return {1.3f, 0.9f, 1.2f, 1.0f}; }
};

class SpellDealer : public Job {
public:
    std::string getName() const override { return "SpellDealer"; }
    StatMultiplier getMultiplier() const override { return {1.5f, 0.8f, 1.1f, 0.9f}; }
};

class Tanker : public Job {
public:
    std::string getName() const override { return "Tanker"; }
    StatMultiplier getMultiplier() const override { return {0.9f, 1.5f, 0.8f, 1.5f}; }
};

class Healer : public Job {
public:
    std::string getName() const override { return "Healer"; }
    StatMultiplier getMultiplier() const override { return {1.0f, 1.1f, 1.0f, 1.1f}; }
};

class NoneJob : public Job {
public:
    std::string getName() const override { return "None"; }
    StatMultiplier getMultiplier() const override { return {1.0f, 1.0f, 1.0f, 1.0f}; }
};
