#include "MoneyBlock.h"

MoneyBlock::MoneyBlock(std::string name, int amount, MoneyType mt)
    : NonProperty{name}, amount{amount}, mt{mt} {}

void MoneyBlock::action(Player &player) {
  if (type == ADD) {
    player.addMoney(amount);
  } else if (type == TO_BLOCK) {
    player.removeMoney(amount);
  }
}