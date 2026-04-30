#include "Event.h"
#include "Player.h"
#include "UI.h"

void LuckBoostEvent::execute(Player* player) {
    player->addLuckBuff(10);
    UI::PrintMessage("A mystical fairy blesses you! LUCK +10 for this run!");
}

std::string LuckBoostEvent::getName() const {
    return "Luck Boost";
}
