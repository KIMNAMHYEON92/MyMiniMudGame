#include "Monster.h"

Monster::Monster(int atk, int def, int spd, int maxHp, const string& name, int expReward)
    :Character(atk, def, spd, maxHp), name(name), expReward(expReward), isElite(false)
{
    skills.push_back(std::make_unique<BasicAttack>());
}

vector<Skill*> Monster::getActiveSkills() const {
    vector<Skill*> rawSkills;
    for (const auto& skill : skills) {
        rawSkills.push_back(skill.get());
    }
    return rawSkills;
}

void Monster::makeElite()
{
    isElite = true;
    name = "[Elite] " + name;

    baseStat.atk = (int)(baseStat.atk * 1.5);
    baseStat.def = (int)(baseStat.def * 1.5);
    baseStat.spd = (int)(baseStat.spd * 1.5);
    baseStat.maxHp = (int)(baseStat.maxHp * 1.5);
    hp = getFinalMaxHp();

    if (!code.empty()) {
        int elementIndex = code[2];
        if (elementIndex == 0) { // Fire
            skills.push_back(std::make_unique<HeavyStrike>());
        } else if (elementIndex == 1) { // Wind
            skills.push_back(std::make_unique<CounterAttack>());
        } else if (elementIndex == 2) { // Water
            skills.push_back(std::make_unique<HealSkill>());
        } else if (elementIndex == 3) { // Soil
            skills.push_back(std::make_unique<HeavyStrike>());
        }
    }
}

void Monster::naming()
{
    vector<int> stats = {getFinalAtk(), getFinalDef(), getFinalSpd(), getFinalMaxHp() / 10};

    vector<string> prefix = {"Sunlight ", "Moonlight ", "Hot ", "Cold ", "Healthy ", "Solid ", "Dirty "};
    vector<string> suffix = {"Pride, ", "Gluttony, ", "Greed, ", "Sloth, ", "Lust, ", "Wrath, ", "Envy, "};
    vector<string> element = {"Fire ", "Wind ", "Water ", "Soil "};
    vector<string> tribe = {"Beast", "Demon", "Undead", "Villain", "Ghost"};

    vector<vector<string>> categories = {prefix, suffix, element, tribe};

    name = ""; 

    for (size_t i = 0; i < categories.size(); ++i)
    {
        const vector<string>& currentCategory = categories[i];
        
        int index = stats[i] % currentCategory.size();
        
        name += currentCategory[index];
        code.push_back(index);
    }
}