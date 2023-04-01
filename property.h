#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>

#include "block.h"

const int MAX_UPGRADES = 5;  // define max_upgrades here as a constant variable
class Property : public Block {
  int improvLvl, purchaseCost, improvCost;

 public:
  Property(int improvLvl, int purchaseCost, int improvCost);
  int getLvl();
  int getPurCost();
  int getImpCost();
  bool upgrade();
};

#endif