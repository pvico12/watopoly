#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>
#include <vector>

#include "block.h"

class Property : public Block {
 protected:
  int improvLvl, purchaseCost;

 public:
  Property(std::string name, int purchaseCost, int improvLvl);
  int getLvl();
  int getPurCost();
  virtual bool upgrade() = 0;
  virtual int getFee() = 0;
};

#endif