#include "money.h"

MoneyBlock::MoneyBlock(std::string name, int amount, MoneyType mt)
    : NonProperty{name}, amount{amount}, mt{mt} {}

void MoneyBlock::action(Player &player) {
  if (mt == ADD) {
    player.addMoney(amount);
  } else if (mt == REMOVE) {
    // need to set a separate case for when the player doesn't have enough money
    player.removeMoney(amount);
  }
}