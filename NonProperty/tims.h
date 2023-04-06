#ifndef TIMS_H
#define TIMS_H

#include <vector>

#include "nonproperty.h"

class Tims : public NonProperty {
  std::vector<Player> players;

 public:
  Tims(std::string name);
  virtual void action(Player &player) override;
};

#endif