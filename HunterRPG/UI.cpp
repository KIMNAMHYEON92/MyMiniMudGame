#include "UI.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

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

void UI::PrintMonsterStatus(const string& name, int rank, int hp, int maxHp, int atk, int def, int spd)
{
    PrintLine('*');
    cout << " | " << left << setw(12) << "Enemy Name" << " : " << setw(14) << name
         << " | " << setw(10) << "Rank" << " : " << setw(12) << rank << " |\n";
    cout << " | " << left << setw(12) << "HP" << " : " << hp << " / " << setw(9) << maxHp
         << " | " << setw(10) << "ATK" << " : " << setw(12) << atk << " |\n";
    cout << " | " << left << setw(12) << "DEF" << " : " << setw(14) << def
         << " | " << setw(10) << "SPD" << " : " << setw(12) << spd << " |\n";
    PrintLine('*');
}

void UI::PrintMessage(const string& msg)
{
    cout << "  ▶ " << msg << "\n";
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
