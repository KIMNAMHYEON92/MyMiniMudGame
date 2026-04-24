#include <iostream>
#include <string>
#include <vector>

#include "Player.h"
#include "Monster.h"

using namespace std;

int main(int argc, char* argv[])
{
    string nick;
    string characterClass = "None";
    int classChoiceInput;
    vector<int> classBonus;
    
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
    
    Player player = Player(classBonus[0],classBonus[1],classBonus[2],classBonus[3],nick,characterClass);
    cout << "Creation Bonus! \n\n";
    player.gainExp(0);
    
    cout << "status \n";
    cout << "level: " << player.getLevel() << "\n";
    cout << "ATK: " << player.getAtk() << "\n";
    cout << "DEF: " << player.getDef() << "\n";
    cout << "SPD: " << player.getSpd() << "\n";
    cout << "HP: " << player.getHp() << " / " << player.getMaxHp() << "\n\n";
    
    while (player.isAlive())
    {
        int minDifficulty = player.getLevel()-2;
        int maxDifficulty = player.getLevel();
        int gateChoice;
        vector<int> monBaseStat;
        cout << "choose the gate, Hunter " << player.getNick() << "\n";
        cout << "1. Green Gate (-2 ~ 0 to difficulty) \n";
        cout << "2. Yellow Gate (-1 ~ +1 to difficulty) \n";
        cout << "3. Red Gate (0 ~ 2 to difficulty) \n";
        cout << "4. Chaos Gate (-5 ~ +5 to difficulty) \n";
        cin >> gateChoice;
        
        switch (gateChoice)
        {
        case 1:
            cout << "Entered the green gate";
            break;
        case 2:
            minDifficulty +=1;
            maxDifficulty +=1;
            break;
        case 3:
            minDifficulty +=2;
            maxDifficulty +=2;
            break;
        case 4:
            minDifficulty -=3;
            maxDifficulty +=5;
            break;
        default:
            break;
        }
    }
    
    return 0;
}
