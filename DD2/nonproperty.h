#ifndef NONPROPERTY_H
#define NONPROPERTY_H

#include <string>

#include "block.h"
#include "player.h"

class NonProperty : public Block {
  // Decorator Pattern
 public:
  NonProperty(std::string name);
  virtual void action(Player &player) = 0;
};

#endif
