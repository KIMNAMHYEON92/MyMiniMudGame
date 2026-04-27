#include "Monster.h"

Monster::Monster(int atk, int def, int spd, int maxHp, const string& name, int expReward)
    :Character(atk, def, spd, maxHp), name(name), expReward(expReward){}

void Monster::naming()
{
    vector<int> baseStat = {atk, def, spd, maxHp / 10};

    vector<string> prefix = {"Sunlight ", "Moonlight ", "Hot ", "Cold ", "Healthy ", "Solid ", "Dirty "};
    vector<string> suffix = {"Pride, ", "Gluttony, ", "Greed, ", "Sloth, ", "Lust, ", "Wrath, ", "Envy, "};
    vector<string> element = {"Fire ", "Wind ", "Water ", "Soil "};
    vector<string> tribe = {"Beast", "Demon", "Undead", "Villain", "Ghost"};

    vector<vector<string>> categories = {prefix, suffix, element, tribe};

    name = ""; 

    for (size_t i = 0; i < categories.size(); ++i)
    {
        const vector<string>& currentCategory = categories[i];
        
        int index = baseStat[i] % currentCategory.size();
        
        name += currentCategory[index];
        code.push_back(index);
    }
}