#include "Battle.h"
#include "UI.h"
#include <iostream>

using namespace std;

Battle::Battle(Player& player, Monster& monster): player(player), monster(monster){}

bool Battle::run()
{
    UI::ClearScreen();
    UI::PrintTitle("Battle Start with " + monster.getName());
    UI::PrintMonsterStatus(monster.getName(), monster.getExpReward(), monster.getHp(), monster.getMaxHp(), monster.getAtk(), monster.getDef(), monster.getSpd());
    cout << "\n";
    
    UI::Pause();
    while (player.getHp()>0 && monster.getHp()>0)
    {
        UI::ClearScreen();
        UI::PrintTitle("Battle: " + player.getNick() + " vs " + monster.getName());
        cout << "\n";

        if (player.getSpd()>monster.getSpd())
        {
            monster.takeDamage(player.attack());
            UI::PrintMessage(player.getNick() + " attacks! " + monster.getName() + "'s HP -" + to_string(player.getAtk()));
            if (monster.isAlive())
            {
                player.takeDamage(monster.attack());
                UI::PrintMessage(monster.getName() + " attacks! " + player.getNick() + "'s HP -" + to_string(monster.getAtk()));
            }
            else
            {
                UI::PrintMessage("Last hit to " + monster.getName() + "!");
            }
        }
        else
        {
            player.takeDamage(monster.attack());
            UI::PrintMessage(monster.getName() + " attacks! " + player.getNick() + "'s HP -" + to_string(monster.getAtk()));
            if (player.isAlive())
            {
                monster.takeDamage(player.attack());
                UI::PrintMessage(player.getNick() + " attacks! " + monster.getName() + "'s HP -" + to_string(player.getAtk()));
            }
            else
            {
                UI::PrintMessage("Last hit to " + player.getNick() + "!");
            }
        }
        cout << "\n";

        UI::PrintHealthBar(player.getNick(), player.getHp(), player.getMaxHp());
        UI::PrintHealthBar(monster.getName(), monster.getHp(), monster.getMaxHp());
        cout << "\n";

        UI::Pause();
    }
    if (player.isAlive())
    {
        player.gainExp(monster.getExpReward());
        player.Loot(monster.getExpReward());
    }

    cout << "\n";
    UI::Pause();
    return player.isAlive();
}
