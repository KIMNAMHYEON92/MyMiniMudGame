#include "AsciiArtManager.h"
#include <vector>
#include <sstream>
#include <fstream>

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

vector<string> readLinesFromFile(const string& filename, const vector<string>& fallback) {
    vector<string> lines;
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
        if (!lines.empty()) {
            return lines;
        }
    }
    return fallback;
}

string AsciiArtManager::GenerateMonsterArt(int atk, int def, int spd, int maxHp) {
    vector<int> baseStat = {atk, def, spd, maxHp / 10};

    vector<string> fallback_heads = {
        "   (o_o)   ",
        "   [>_<]   ",
        "   {^o^}   ",
        "   (X_X)   ",
        "   <T_T>   "
    };
    vector<string> heads = readLinesFromFile("data/heads.txt", fallback_heads);

    vector<string> fallback_bodies = {
        "  /|===|\\  ",
        "  \\|===|/  ",
        "   |HHH|   ",
        "  <|ooo|>  ",
        "   (###)   "
    };
    vector<string> bodies = readLinesFromFile("data/bodies.txt", fallback_bodies);

    vector<string> fallback_weapons = {
        " ---/|     ",
        " ---===    ",
        "   o==>    ",
        "   )==>    ",
        "   ]==>    "
    };
    vector<string> weapons = readLinesFromFile("data/weapons.txt", fallback_weapons);

    vector<string> fallback_legs = {
        "   /   \\   ",
        "  |     |  ",
        "   \\   /   ",
        "   <   >   ",
        "   ]   [   "
    };
    vector<string> legs = readLinesFromFile("data/legs.txt", fallback_legs);

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
