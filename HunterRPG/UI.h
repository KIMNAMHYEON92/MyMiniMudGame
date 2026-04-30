#pragma once
#include <string>
#include <vector>

class Monster;

class UI
{
public:
    // 화면 초기화 및 일시정지 (플랫폼 호환성 고려)
    static void ClearScreen();
    static void Pause();

    // 장식용 경계선 출력
    static void PrintLine(char c = '=', int length = 60);

    // 중앙 정렬된 타이틀 출력
    static void PrintTitle(const std::string& title);

    // 메뉴 출력
    static void PrintMenu(const std::string& title, const std::vector<std::string>& options);

    // 플레이어 상태창 출력 (MUD 게임 스타일)
    static void PrintStatus(const std::string& name, const std::string& job, int level, int hp, int maxHp, int atk, int def, int spd);

    // 몬스터 상태창 출력
    static void PrintMonsterStatus(const std::string& name, int rank, int hp, int maxHp, int atk, int def, int spd);

    // 게임 내 시스템/전투 메시지 출력
    static void PrintMessage(const std::string& msg);
    
    // 체력바(HP Bar) 시각화 출력
    static void PrintHealthBar(const std::string& name, int currentHp, int maxHp, int length = 20);

    // Gate Progression Visual
    static void PrintGateProgression(int currentIndex, const std::vector<Monster>& monsters);
};
