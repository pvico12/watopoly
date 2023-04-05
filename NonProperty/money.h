#ifndef MONEYBLOCK_H
#define MONEYBLOCK_H

#include "nonproperty.h"
#include "../player.h"

enum MoneyType {
  ADD,
  REMOVE
};

class MoneyBlock : public NonProperty {
  int amount;
  MoneyType mt;

 public:
  MoneyBlock(std::string name, int amount, MoneyType mt);
  virtual void action(Player &player);
};

#endif