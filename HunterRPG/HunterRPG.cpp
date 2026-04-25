#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Battle.h"
#include "Player.h"
#include "Monster.h"

using namespace std;

int main(int argc, char* argv[])
{
    string nick;
    string characterClass = "None";
    int classChoiceInput;
    vector<int> classBonus;
    int turn = 0;
    int basenum = 3;
    
    system("cls");
    cout << "nickname : ";
    cin >> nick;
    cout << "\n";
    
    cout << "character class choice" << "\n";
    cout << "1. Melee Dealer (ATK: 2, DEF: 2, SPD: 2, MAX HP: 20) \n";
    cout << "2. Range Dealer (ATK: 3, DEF: 1, SPD: 3, MAX HP: 10) \n";
    cout << "3. Spell Dealer (ATK: 4, DEF: 1, SPD: 2, MAX HP: 10) \n";
    cout << "4. Tanker (ATK: 1, DEF: 3, SPD: 1, MAX HP: 30) \n";
    cout << "5. Healer (ATK: 1, DEF: 1, SPD: 1, MAX HP: 50) \n";
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
        cout << "\n[System] wrong choice, default class None (ATK: 1, DEF: 1, SPD: 1, MAX HP: 10) \n";
        break;
    }
    cout << "\n";
    system("cls");
    Player player = Player(classBonus[0],classBonus[1],classBonus[2],classBonus[3],nick,characterClass);
    cout << "Creation Bonus! \n\n";
    player.gainExp(1);
    
    cout << "status \n";
    cout << "level: " << player.getLevel() << "\n";
    cout << "ATK: " << player.getAtk() << "\n";
    cout << "DEF: " << player.getDef() << "\n";
    cout << "SPD: " << player.getSpd() << "\n";
    cout << "HP: " << player.getHp() << " / " << player.getMaxHp() << "\n\n";
    
    system("pause");
    
    srand((unsigned int)time(NULL));
    while (player.isAlive())
    {
        system("cls");
        cout << "Day " << ++turn << " start\n";
        int minDifficulty = player.getLevel();
        int maxDifficulty = player.getLevel()+2;
        int gateChoice;
        vector<int> monBaseStat;
        cout << "choose the gate, Hunter " << player.getNick() << "\n";
        cout << "1. Green Gate (0 ~ 2 to difficulty) \n";
        cout << "2. Yellow Gate (+1 ~ +3 to difficulty) \n";
        cout << "3. Red Gate (+2 ~ +4 to difficulty) \n";
        cout << "4. Chaos Gate (0 ~ +10 to difficulty) \n";
        cout << "choose your gate number : ";
        cin >> gateChoice;
        
        switch (gateChoice)
        {
        case 1:
            cout << "Entered the green gate\n";
            break;
        case 2:
            cout << "Entered the Yellow gate\n";
            minDifficulty +=1;
            maxDifficulty +=1;
            break;
        case 3:
            cout << "Entered the Red gate\n";
            minDifficulty +=2;
            maxDifficulty +=2;
            break;
        case 4:
            cout << "Entered the Chaos gate\n";
            maxDifficulty +=8;
            break;
        default:
            cout << "Entered the Chaos gate\n";
            maxDifficulty +=8;
            break;
        }
        
        vector<Monster> monsters;
        int spawnRange = maxDifficulty - minDifficulty;
        int numMonsters = basenum + rand()%3 + (turn/7);
        cout << numMonsters << " monsters in gate\n";
        cout << "Scouting results detected, ";
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
        cout << "monsters respectively.\n";
        system("pause");
        
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
        int score = player.getScore();
        cout << "gameover! score: " << score << " \n";
    }
    
    return 0;
}
