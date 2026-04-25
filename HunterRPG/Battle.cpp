#include "Battle.h"
#include <iostream>

Battle::Battle(Player& player, Monster& monster): player(player), monster(monster){}

bool Battle::run()
{
    system("cls");
    cout << "Battle Start with " << monster.getName() << "\n";
    cout << "ATK: " << monster.getAtk() << ", DEF: " << monster.getDef() << ", SPD: " << monster.getSpd() << ", HP: " << monster.getHp() << "\n";
    
    system("pause");
    while (player.getHp()>0 && monster.getHp()>0)
    {
        system("cls");
        if (player.getSpd()>monster.getSpd())
        {
            monster.takeDamage(player.attack());
            cout << player.getNick() << " attack! " << monster.getName() << "'s HP -" << player.getAtk() << "\n";
            if (monster.isAlive())
            {
                player.takeDamage(monster.attack());
                cout << monster.getName() << " attack! " << player.getNick() << "'s HP -" << monster.getAtk() << "\n";
            }
            else
            {
                cout << "Last hit to " << monster.getName() << " !\n";
            }
        }
        else
        {
            player.takeDamage(monster.attack());
            cout << monster.getName() << " attack! " << player.getNick() << "'s HP -" << monster.getAtk() << "\n";
            if (player.isAlive())
            {
                monster.takeDamage(player.attack());
                cout << player.getNick() << " attack! " << monster.getName() << "'s HP -" << player.getAtk() << "\n";
            }
            else
            {
                cout << "Last hit to " << player.getNick() << " !\n";
            }
        }
        cout << "\n";
        cout << player.getNick() << "\n";
        cout << "HP: " << player.getHp() << " / " << player.getMaxHp();
        cout << ", (LEVEL: " << player.getLevel() << ", ATK: " << player.getAtk();
        cout << ", DEF: " << player.getDef() << ", SPD: " << player.getSpd() << ")\n";
        cout << monster.getName() << "\n";
        cout << "HP: " << monster.getHp() << " / " << monster.getMaxHp();
        cout << ", (RANK: " << monster.getExpReward() << ", ATK: " << monster.getAtk();
        cout << ", DEF: " << monster.getDef() << ", SPD: " << monster.getSpd() << ")\n";
        system("pause");
    }
    if (player.isAlive())
    {
        player.gainExp(monster.getExpReward());
        player.Loot(monster.getExpReward());
    }
    system("pause");
    return player.isAlive();
}
