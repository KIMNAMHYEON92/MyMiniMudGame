#pragma once

#include <string>

class Player;

class Event {
public:
    virtual ~Event() = default;
    virtual void execute(Player* player) = 0;
    virtual std::string getName() const = 0;
};

class LuckBoostEvent : public Event {
public:
    void execute(Player* player) override;
    std::string getName() const override;
};
