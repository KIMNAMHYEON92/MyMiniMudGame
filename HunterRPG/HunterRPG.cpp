#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Battle.h"
#include "Player.h"
#include "Monster.h"
#include "UI.h"

using namespace std;

int main(int argc, char* argv[])
{
    string nick;
    string characterClass = "None";
    int classChoiceInput;
    vector<int> classBonus;
    int turn = 0;
    int basenum = 3;
    
    UI::ClearScreen();
    UI::PrintTitle("HUNTER RPG");
    cout << "nickname : ";
    cin >> nick;
    cout << "\n";
    
    vector<string> classOptions = {
        "Melee Dealer (ATK: 2, DEF: 2, SPD: 2, MAX HP: 20)",
        "Range Dealer (ATK: 3, DEF: 1, SPD: 3, MAX HP: 10)",
        "Spell Dealer (ATK: 4, DEF: 1, SPD: 2, MAX HP: 10)",
        "Tanker (ATK: 1, DEF: 3, SPD: 1, MAX HP: 30)",
        "Healer (ATK: 1, DEF: 1, SPD: 1, MAX HP: 50)"
    };
    UI::PrintMenu("Character Class Choice", classOptions);
    cout << "choose your class number : ";
    cin >> classChoiceInput;
    
    switch(classChoiceInput)
    {
    case 1: 
        characterClass = "MeleeDealer";
        classBonus={2,2,2,20};
        break;
    case 2: 
        characterClass = "RangeDealer"; 
        classBonus={3,1,3,10};
        break;
    case 3: 
        characterClass = "SpellDealer"; 
        classBonus={4,1,2,10};
        break;
    case 4: 
        characterClass = "Tanker"; 
        classBonus={1,3,1,30};
        break;
    case 5: 
        characterClass = "Healer"; 
        classBonus={1,1,1,50};
        break;
    default:
        characterClass = "None"; 
        classBonus={1,1,1,10};
        UI::PrintMessage("Wrong choice, default class None (ATK: 1, DEF: 1, SPD: 1, MAX HP: 10)");
        break;
    }
    cout << "\n";
    UI::ClearScreen();
    Player player = Player(classBonus[0],classBonus[1],classBonus[2],classBonus[3],nick,characterClass);
    UI::PrintMessage("Creation Bonus!");
    player.gainExp(5);
    UI::Pause();
    
    UI::ClearScreen();
    UI::PrintStatus(player.getNick(), player.getCharacterClass(), player.getLevel(), player.getHp(), player.getMaxHp(), player.getAtk(), player.getDef(), player.getSpd());
    cout << "\n";
    
    UI::Pause();
    
    srand((unsigned int)time(NULL));
    while (player.isAlive())
    {
        UI::ClearScreen();
        UI::PrintTitle("Day " + to_string(++turn) + " Start");
        int minDifficulty = player.getLevel();
        int maxDifficulty = player.getLevel()+2;
        int gateChoice;
        vector<int> monBaseStat;

        vector<string> gateOptions = {
            "Green Gate (0 ~ +2 to difficulty)",
            "Yellow Gate (+1 ~ +3 to difficulty)",
            "Red Gate (+2 ~ +4 to difficulty)",
            "Chaos Gate (0 ~ +10 to difficulty)"
        };
        UI::PrintMenu("Choose the Gate, Hunter " + player.getNick(), gateOptions);
        cout << "choose your gate number : ";
        cin >> gateChoice;
        
        switch (gateChoice)
        {
        case 1:
            UI::PrintMessage("Entered the Green Gate");
            break;
        case 2:
            UI::PrintMessage("Entered the Yellow Gate");
            minDifficulty +=1;
            maxDifficulty +=1;
            break;
        case 3:
            UI::PrintMessage("Entered the Red Gate");
            minDifficulty +=2;
            maxDifficulty +=2;
            break;
        case 4:
            UI::PrintMessage("Entered the Chaos Gate");
            maxDifficulty +=8;
            break;
        default:
            UI::PrintMessage("Entered the Chaos Gate");
            maxDifficulty +=8;
            break;
        }
        
        vector<Monster> monsters;
        int spawnRange = maxDifficulty - minDifficulty;
        int numMonsters = basenum + rand()%3 + (turn/7);
        UI::PrintMessage(to_string(numMonsters) + " monsters in gate");
        cout << "  * Scouting results detected: ";
        for (int i=0;i<numMonsters;i++)
        {
            int range = spawnRange +1;
            int spawnPower = minDifficulty + rand()%range;
            cout << spawnPower << " Rank, ";
            monBaseStat = {0,0,0,0};
            for (int j=0;j<spawnPower;j++)
            {
                int stat = rand()%4;
                monBaseStat[stat]++;
            }
            int atk = 1 + (turn/7) + monBaseStat[0];
            int def = 1 + (turn/7) + monBaseStat[1];
            int spd = 1 + (turn/7) + monBaseStat[2];
            int maxHp = 10 * (1 + (turn/7) + monBaseStat[3]);
            monsters.push_back(Monster(atk,def,spd,maxHp,"",spawnPower));
        }
        cout << "monsters respectively.\n\n";
        UI::Pause();
        
        for (Monster mon : monsters)
        {
            mon.naming();
            Battle battle = Battle(player,mon);
            bool result = battle.run();
            if (!result) break;
        }
        
        if (!player.isAlive()) break;
    }
    if (!player.isAlive())
    {
        UI::ClearScreen();
        UI::PrintTitle("GAME OVER");
        int score = player.getScore();
        UI::PrintMessage("Score: " + to_string(score));
        cout << "\n";
    }
    
    return 0;
}
