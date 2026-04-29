#include "Battle.h"
#include "UI.h"
#include "AsciiArtManager.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

Battle::Battle(Player& player, Monster& monster): player(player), monster(monster){}

bool Battle::run()
{
    UI::ClearScreen();
    UI::PrintTitle("Battle Start with " + monster.getName());
    cout << AsciiArtManager::GenerateMonsterArt(monster.getFinalAtk(), monster.getFinalDef(), monster.getFinalSpd(), monster.getFinalMaxHp()) << "\n";
    UI::PrintMonsterStatus(monster.getName(), monster.getExpReward(), monster.getHp(), monster.getFinalMaxHp(), monster.getFinalAtk(), monster.getFinalDef(), monster.getFinalSpd());
    cout << "\n";
    
    UI::Pause();
    while (player.getHp()>0 && monster.getHp()>0)
    {
        UI::ClearScreen();
        UI::PrintTitle("Battle: " + player.getNick() + " vs " + monster.getName());
        cout << "\n";

        if (player.getFinalSpd() > monster.getFinalSpd())
        {
            cout << "  /// SLASH ///\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            int dmg = monster.takeDamage(player.attack());
            UI::PrintMessage(player.getNick() + " attacks! " + monster.getName() + "'s HP -" + to_string(dmg));
            if (monster.isAlive())
            {
                cout << "  *** SMASH ***\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                int mdmg = player.takeDamage(monster.attack());
                UI::PrintMessage(monster.getName() + " attacks! " + player.getNick() + "'s HP -" + to_string(mdmg));
            }
            else
            {
                UI::PrintMessage("Last hit to " + monster.getName() + "!");
            }
        }
        else
        {
            cout << "  *** SMASH ***\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            int mdmg = player.takeDamage(monster.attack());
            UI::PrintMessage(monster.getName() + " attacks! " + player.getNick() + "'s HP -" + to_string(mdmg));
            if (player.isAlive())
            {
                cout << "  /// SLASH ///\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                int dmg = monster.takeDamage(player.attack());
                UI::PrintMessage(player.getNick() + " attacks! " + monster.getName() + "'s HP -" + to_string(dmg));
            }
            else
            {
                UI::PrintMessage("Last hit to " + player.getNick() + "!");
            }
        }
        cout << "\n";

        UI::PrintHealthBar(player.getNick(), player.getHp(), player.getFinalMaxHp());
        UI::PrintHealthBar(monster.getName(), monster.getHp(), monster.getFinalMaxHp());
        cout << "\n";

        UI::Pause();
    }
    if (player.isAlive())
    {
        player.gainExp(monster.getExpReward());
    }

    cout << "\n";
    UI::Pause();
    return player.isAlive();
}
