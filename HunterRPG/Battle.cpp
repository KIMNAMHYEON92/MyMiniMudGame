#include "Battle.h"
#include "UI.h"
#include "AsciiArtManager.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <cmath>
#include "Skill.h"

using namespace std;

bool checkSkillProbability(int baseProb, int effectiveLuck) {
    int totalRolls = 1 + (std::abs(effectiveLuck) / 100);
    if ((std::rand() % 100) < (std::abs(effectiveLuck) % 100)) {
        totalRolls += 1;
    }

    if (effectiveLuck >= 0) {
        for (int i = 0; i < totalRolls; ++i) {
            if ((std::rand() % 100) < baseProb) {
                return true;
            }
        }
        return false;
    } else {
        for (int i = 0; i < totalRolls; ++i) {
            if ((std::rand() % 100) >= baseProb) {
                return false;
            }
        }
        return true;
    }
}

Battle::Battle(Player& player, Monster& monster): player(player), monster(monster){}

bool Battle::run(int gateIndex, const std::vector<Monster>& monsters)
{
    UI::RenderBattle(player, monster, gateIndex, monsters);
    UI::Pause();
    auto evaluateTriggers = [&](Character* character, Trigger triggerType, int effectiveLuck) {
        for (Skill* skill : character->getActiveSkills()) {
            if (skill->trigger == triggerType) {
                if (checkSkillProbability(skill->baseProbability, effectiveLuck)) {
                    skill->isCharged = true;
                }
            }
        }
    };

    auto executeAttackPhase = [&](Character* attacker, Character* defender, int attackerLuck, int defenderLuck, std::string attackText, std::string attackerName, std::string defenderName) {
        evaluateTriggers(defender, Trigger::ON_DEFEND, defenderLuck);

        std::vector<Skill*> defendSkills;
        for (Skill* skill : defender->getActiveSkills()) {
            if (skill->trigger == Trigger::ON_DEFEND && skill->isCharged) {
                defendSkills.push_back(skill);
            }
        }
        if (!defendSkills.empty()) {
            Skill* chosenSkill = defendSkills[std::rand() % defendSkills.size()];
            chosenSkill->execute(defender, attacker);
            chosenSkill->isCharged = false;
        }

        if (!attacker->isAlive() || !defender->isAlive()) return;

        evaluateTriggers(attacker, Trigger::ON_ATTACK, attackerLuck);

        std::vector<Skill*> attackSkills;
        int maxPriority = -1;

        for (Skill* skill : attacker->getActiveSkills()) {
            if (skill->trigger == Trigger::ON_ATTACK && skill->isCharged) {
                if (skill->priority > maxPriority) {
                    maxPriority = skill->priority;
                    attackSkills.clear();
                    attackSkills.push_back(skill);
                } else if (skill->priority == maxPriority) {
                    attackSkills.push_back(skill);
                }
            }
        }

        if (!attackSkills.empty()) {
            UI::PrintMessage(attackText);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));

            Skill* chosenSkill = attackSkills[std::rand() % attackSkills.size()];
            chosenSkill->execute(attacker, defender);
            chosenSkill->isCharged = false;
        }
    };

    while (player.getHp()>0 && monster.getHp()>0)
    {
        evaluateTriggers(&player, Trigger::ON_TURN_START, player.getFinalLuck());
        for (Skill* skill : player.getActiveSkills()) {
            if (skill->trigger == Trigger::ON_TURN_START && skill->isCharged) {
                skill->execute(&player, &monster);
                skill->isCharged = false;
            }
        }

        evaluateTriggers(&monster, Trigger::ON_TURN_START, -player.getFinalLuck());
        for (Skill* skill : monster.getActiveSkills()) {
            if (skill->trigger == Trigger::ON_TURN_START && skill->isCharged) {
                skill->execute(&monster, &player);
                skill->isCharged = false;
            }
        }

        if (!player.isAlive() || !monster.isAlive()) break;

        if (player.getFinalSpd() > monster.getFinalSpd())
        {
            executeAttackPhase(&player, &monster, player.getFinalLuck(), -player.getFinalLuck(), "/// SLASH ///", player.getNick(), monster.getName());
            if (monster.isAlive() && player.isAlive())
            {
                executeAttackPhase(&monster, &player, -player.getFinalLuck(), player.getFinalLuck(), "*** SMASH ***", monster.getName(), player.getNick());
            }
        }
        else
        {
            executeAttackPhase(&monster, &player, -player.getFinalLuck(), player.getFinalLuck(), "*** SMASH ***", monster.getName(), player.getNick());
            if (player.isAlive() && monster.isAlive())
            {
                executeAttackPhase(&player, &monster, player.getFinalLuck(), -player.getFinalLuck(), "/// SLASH ///", player.getNick(), monster.getName());
            }
        }

        if (!monster.isAlive()) {
             UI::PrintMessage("Last hit to " + monster.getName() + "!");
        } else if (!player.isAlive()) {
             UI::PrintMessage("Last hit to " + player.getNick() + "!");
        }

        UI::RenderBattle(player, monster, gateIndex, monsters);
        UI::Pause();
    }
    if (player.isAlive())
    {
        player.gainExp(monster.getExpReward());
    }

    player.resetBuffs();
    monster.resetBuffs();

    return player.isAlive();
}
