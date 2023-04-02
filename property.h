#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>
#include <vector>

#include "block.h"

extern const int MAX_UPGRADES;
extern const std::string DASHED_LINE;

class Property : public Block {
  int improvLvl, purchaseCost, improvCost;
  std::vector<int> fees;

 public:
  Property(std::string name, std::vector<int> fees, int purchaseCost, int improvCost, int improvLvl);
  int getLvl();
  int getPurCost();
  int getImpCost();
  bool upgrade();
  bool isMaxUpgrade();
  int getFee();
};

#endif