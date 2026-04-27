#include "AsciiArtManager.h"
#include <vector>
#include <sstream>

using namespace std;

string AsciiArtManager::GetTitleArt() {
    stringstream ss;
    ss << "======================================\n";
    ss << "||                                  ||\n";
    ss << "||         HUNTER RPG               ||\n";
    ss << "||                                  ||\n";
    ss << "======================================\n";
    return ss.str();
}

string AsciiArtManager::GenerateMonsterArt(int atk, int def, int spd, int maxHp) {
    vector<int> baseStat = {atk, def, spd, maxHp / 10};

    vector<string> heads = {
        "   (o_o)   ",
        "   [>_<]   ",
        "   {^o^}   ",
        "   (X_X)   ",
        "   <T_T>   "
    };

    vector<string> bodies = {
        "  /|===|\\  ",
        "  \\|===|/  ",
        "   |HHH|   ",
        "  <|ooo|>  ",
        "   (###)   "
    };

    vector<string> weapons = {
        " ---/|     ",
        " ---===    ",
        "   o==>    ",
        "   )==>    ",
        "   ]==>    "
    };

    vector<string> legs = {
        "   /   \\   ",
        "  |     |  ",
        "   \\   /   ",
        "   <   >   ",
        "   ]   [   "
    };

    int headIndex = baseStat[0] % heads.size();
    int bodyIndex = baseStat[1] % bodies.size();
    int weaponIndex = baseStat[2] % weapons.size();
    int legsIndex = baseStat[3] % legs.size();

    stringstream ss;
    ss << heads[headIndex] << "\n";
    ss << bodies[bodyIndex] << weapons[weaponIndex] << "\n";
    ss << legs[legsIndex] << "\n";

    return ss.str();
}
