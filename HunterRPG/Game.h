#pragma once
#include "Player.h"
#include <memory>
#include <vector>

enum class GameState { MAIN_MENU, CHAR_CREATION, IN_GAME, GAME_OVER, EXIT };

class Game {
public:
    void run();
private:
    int irand(int min,int max);
    void mainMenu();
    void createPlayer();
    void turnLoop();
    void gameOver();

    std::unique_ptr<Player> player;
    std::vector<Stat> lootBox;
    int turn = 0;
    GameState currentState = GameState::MAIN_MENU;
};
