#include "tims.h"

#include <iostream>

Tims::Tims(std::string name) : NonProperty{name} {}

void Tims::action(Player &player) {
  std::cout << "You are currently in DC Tims Line." << std::endl;
  player.move(0);
}