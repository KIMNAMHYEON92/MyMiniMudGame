#include "Game.h"
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <memory>

#include "Battle.h"
#include "Monster.h"
#include "UI.h"
#include "AsciiArtManager.h"
#include "Job.h"

using namespace std;

void Game::run() {
    createPlayer();
    if (player) {
        turnLoop();
        gameOver();
    }
}
int Game::irand(int min,int max)
{    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(min, max);
    return dis(gen);
}

void Game::createPlayer() {
    string nick;
    std::unique_ptr<Job> job;
    int classChoiceInput;
    vector<int> classBonus;

    UI::ClearScreen();
    cout << AsciiArtManager::GetTitleArt();
    UI::Pause();

    UI::ClearScreen();
    UI::PrintTitle("Welcome to HUNTER RPG");
    cout << "nickname : ";
    cin >> nick;
    cout << "\n";

    vector<string> classOptions = {
        "Melee Dealer (ATK: 20, DEF: 20, SPD: 20, MAX HP: 200)",
        "Range Dealer (ATK: 30, DEF: 10, SPD: 30, MAX HP: 100)",
        "Spell Dealer (ATK: 40, DEF: 10, SPD: 20, MAX HP: 100)",
        "Tanker (ATK: 10, DEF: 30, SPD: 10, MAX HP: 300)",
        "Healer (ATK: 10, DEF: 10, SPD: 10, MAX HP: 500)"
    };
    UI::PrintMenu("Character Class Choice", classOptions);
    cout << "choose your class number : ";
    cin >> classChoiceInput;

    switch(classChoiceInput)
    {
    case 1:
        job = std::make_unique<MeleeDealer>();
        classBonus={20,20,20,200};
        break;
    case 2:
        job = std::make_unique<RangeDealer>();
        classBonus={30,10,30,100};
        break;
    case 3:
        job = std::make_unique<SpellDealer>();
        classBonus={40,10,20,100};
        break;
    case 4:
        job = std::make_unique<Tanker>();
        classBonus={10,30,10,300};
        break;
    case 5:
        job = std::make_unique<Healer>();
        classBonus={10,10,10,500};
        break;
    default:
        job = std::make_unique<NoneJob>();
        classBonus={10,10,10,100};
        UI::PrintMessage("Wrong choice, default class None (ATK: 10, DEF: 10, SPD: 10, MAX HP: 100)");
        break;
    }
    cout << "\n";
    UI::ClearScreen();

    player = std::make_unique<Player>(classBonus[0],classBonus[1],classBonus[2],classBonus[3],nick,std::move(job));

    UI::PrintMessage("Creation Bonus!");
    player->gainExp(5);
    UI::Pause();

    UI::ClearScreen();
    UI::PrintStatus(player->getNick(), player->getCharacterClass(), player->getLevel(), player->getHp(), player->getFinalMaxHp(), player->getFinalAtk(), player->getFinalDef(), player->getFinalSpd());
    cout << "\n";

    UI::Pause();
}

void Game::turnLoop() {
    
    int basenum = 3;
    

    while (player->isAlive())
    {
        UI::ClearScreen();
        UI::PrintTitle("Day " + to_string(++turn) + " Start");
        int minDifficulty = player->getLevel();
        int maxDifficulty = player->getLevel()+2;
        int gateChoice;
        vector<int> monBaseStat;

        vector<string> gateOptions = {
            "Green Gate (0 ~ +2 to difficulty)",
            "Yellow Gate (+1 ~ +3 to difficulty)",
            "Red Gate (+2 ~ +4 to difficulty)",
            "Chaos Gate (0 ~ +10 to difficulty)"
        };
        UI::PrintMenu("Choose the Gate, Hunter " + player->getNick(), gateOptions);
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
        int numMonsters = basenum + irand(0,2) + (turn/7);
        UI::PrintMessage(to_string(numMonsters) + " monsters in gate");
        cout << "  * Proceeding into the gate...\n\n";
        for (int i=0;i<numMonsters;i++)
        {
            int range = spawnRange +1;
            int spawnPower = minDifficulty + irand(0,range-1);
            monBaseStat = {0,0,0,0};
            for (int j=0;j<spawnPower;j++)
            {
                int stat = irand(0,3);
                monBaseStat[stat]++;
            }
            int atk = 10 * (1 + (turn/7) + monBaseStat[0]);
            int def = 10 * (1 + (turn/7) + monBaseStat[1]);
            int spd = 10 * (1 + (turn/7) + monBaseStat[2]);
            int maxHp = 100 * (1 + (turn/7) + monBaseStat[3]);
            monsters.push_back(Monster(atk,def,spd,maxHp,"",spawnPower));
        }
        UI::Pause();

        int monIndex = 0;
        for (Monster& mon : monsters)
        {
            UI::ClearScreen();
            UI::PrintGateProgression(monIndex, numMonsters);
            cout << "\n";
            UI::Pause();

            mon.naming();
            Battle battle = Battle(*player,mon);
            bool result = battle.run();
            if (!result) break;

            if (player->isAlive()) {
                lootBox.push_back(player->generateLoot(mon.getExpReward()));
            }
            monIndex++;
        }

        if (player->isAlive() && !lootBox.empty()) {
            UI::ClearScreen();
            UI::PrintTitle("Item Appraisal");
            cout << "  * You cleared the gate! Appraisal time for looted items:\n\n";
            for (size_t i = 0; i < lootBox.size(); i++) {
                Stat loot = lootBox[i];
                cout << "  [Loot " << (i+1) << "] ATK:+" << loot.atk << " DEF:+" << loot.def << " SPD:+" << loot.spd << " HP:+" << loot.maxHp << "\n";
            }
            cout << "\n";
            cout << "  Current Item Stats -> ATK:+" << player->getItemStat().atk << " DEF:+" << player->getItemStat().def << " SPD:+" << player->getItemStat().spd << " HP:+" << player->getItemStat().maxHp << "\n";
            cout << "\n  Select a loot number to replace your current item (or 0 to skip): ";
            int choice;
            cin >> choice;
            if (choice > 0 && choice <= (int)lootBox.size()) {
                player->applyLoot(lootBox[choice-1]);
                UI::PrintMessage("Item equipped!");
                UI::Pause();
            }
        }
        lootBox.clear();

        if (!player->isAlive()) break;
    }
}

void Game::gameOver() {
    if (!player->isAlive())
    {
        UI::ClearScreen();
        UI::PrintTitle("GAME OVER");
        int score = player->getScore();
        UI::PrintMessage("Score: " + to_string(score));
        cout << "\n";
    }
}
