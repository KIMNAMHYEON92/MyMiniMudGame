#pragma once
#include <string>

class AsciiArtManager {
public:
    static std::string GetTitleArt();
    static std::string GenerateMonsterArt(int atk, int def, int spd, int maxHp);
};
