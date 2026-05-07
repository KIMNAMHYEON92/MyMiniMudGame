#include "UI.h"
#include "Monster.h"
#include "Player.h"
#include "AsciiArtManager.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

std::deque<std::string> UI::messageLog;

void UI::ClearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void UI::Pause()
{
#ifdef _WIN32
    system("pause");
#else
    cout << "Press Enter to continue..." << endl;
    cin.ignore(256, '\n');
#endif
}

void UI::PrintLine(char c, int length)
{
    cout << string(length, c) << "\n";
}

void UI::PrintTitle(const string& title)
{
    PrintLine('=');
    int padding = (60 - title.length()) / 2;
    if (padding > 0)
        cout << string(padding, ' ') << title << "\n";
    else
        cout << title << "\n";
    PrintLine('=');
}

void UI::PrintMenu(const string& title, const vector<string>& options)
{
    if (!title.empty()) {
        PrintTitle(title);
    }
    for (size_t i = 0; i < options.size(); ++i) {
        cout << "  [" << (i + 1) << "] " << options[i] << "\n";
    }
    PrintLine('-');
}

void UI::PrintStatus(const string& name, const string& job, int level, int hp, int maxHp, int atk, int def, int spd)
{
    PrintLine('+');
    cout << " | " << left << setw(12) << "Name" << " : " << setw(14) << name
         << " | " << setw(10) << "Class" << " : " << setw(12) << job << " |\n";
    cout << " | " << left << setw(12) << "Level" << " : " << setw(14) << level
         << " | " << setw(10) << "HP" << " : " << hp << " / " << setw(7) << maxHp << " |\n";
    cout << " | " << left << setw(12) << "ATK" << " : " << setw(14) << atk
         << " | " << setw(10) << "DEF" << " : " << setw(12) << def << " |\n";
    cout << " | " << left << setw(12) << "SPD" << " : " << setw(14) << spd
         << " | " << setw(10) << ""      << "   " << setw(12) << "" << " |\n";
    PrintLine('+');
}

void UI::PrintMonsterStatus(const string& name, int rank, int hp, int maxHp, int atk, int def, int spd, const std::string& skillName, int skillLevel)
{
    PrintLine('*');
    cout << " | " << left << setw(12) << "Enemy Name" << " : " << setw(14) << name
         << " | " << setw(10) << "Rank" << " : " << setw(12) << rank << " |\n";
    cout << " | " << left << setw(12) << "HP" << " : " << hp << " / " << setw(9) << maxHp
         << " | " << setw(10) << "ATK" << " : " << setw(12) << atk << " |\n";
    cout << " | " << left << setw(12) << "DEF" << " : " << setw(14) << def
         << " | " << setw(10) << "SPD" << " : " << setw(12) << spd << " |\n";
    cout << " | " << left << setw(12) << "Skill" << " : " << setw(14) << skillName
         << " | " << setw(10) << "Lv" << " : " << setw(12) << skillLevel << " |\n";
    PrintLine('*');
}

void UI::PrintMessage(const string& msg)
{
    messageLog.push_back("  * " + msg);
    if (messageLog.size() > 10) {
        messageLog.pop_front();
    }
}

void UI::PrintSystemMessage(const string& msg)
{
    cout << "  * " << msg << "\n";
}

void UI::RenderBattle(Player& player, Monster& monster, int gateIndex, const std::vector<Monster>& monsters)
{
    // Clear screen & home cursor using ANSI escape codes
    std::cout << "\033[2J\033[H";

    // Print Battle Title
    PrintTitle("Battle: " + player.getNick() + " vs " + monster.getName());

    // Print Monster Ascii Art
    std::cout << AsciiArtManager::GenerateMonsterArt(monster.getFinalAtk(), monster.getFinalDef(), monster.getFinalSpd(), monster.getFinalMaxHp()) << "\n";

    // Print Gate Progression
    PrintGateProgression(gateIndex, monsters);
    std::cout << "\n";

    // Extract Monster Skill Info
    std::string skillName = "None";
    int skillLevel = 0;
    auto skills = monster.getActiveSkills();
    if (skills.size() > 1) {
        skillName = skills.back()->name;
        skillLevel = skills.back()->level;
    }

    // Print Statuses
    PrintStatus(player.getNick(), player.getCharacterClass(), player.getLevel(), player.getHp(), player.getFinalMaxHp(), player.getFinalAtk(), player.getFinalDef(), player.getFinalSpd());
    PrintMonsterStatus(monster.getName(), monster.getExpReward(), monster.getHp(), monster.getFinalMaxHp(), monster.getFinalAtk(), monster.getFinalDef(), monster.getFinalSpd(), skillName, skillLevel);
    std::cout << "\n";

    // Print Message Log
    PrintLine('=', 60);
    std::cout << "  MESSAGE LOG\n";
    PrintLine('-', 60);
    for (const auto& logMsg : messageLog) {
        std::cout << logMsg << "\n";
    }
    PrintLine('=', 60);
    std::cout << "\n";
}

void UI::PrintHealthBar(const string& name, int currentHp, int maxHp, int length)
{
    if (maxHp <= 0) maxHp = 1;
    if (currentHp < 0) currentHp = 0;

    int filled = (currentHp * length) / maxHp;
    int empty = length - filled;

    cout << " " << left << setw(10) << name << " [";
    cout << string(filled, '#');
    cout << string(empty, '-');
    cout << "] " << currentHp << " / " << maxHp << "\n";
}

void UI::PrintGateProgression(int currentIndex, const std::vector<Monster>& monsters)
{
    cout << "  Gate Progress: [Entrance] -> ";
    for (size_t i = 0; i < monsters.size(); ++i) {
        if ((int)i < currentIndex) {
            cout << "[X] -> ";
        } else if ((int)i == currentIndex) {
            cout << "[*YOU*] -> ";
        } else {
            if (monsters[i].getIsElite()) {
                cout << "[E" << (i+1) << "] -> ";
            } else {
                cout << "[M" << (i+1) << "] -> ";
            }
        }
    }
    cout << "[Clear]\n";
}
