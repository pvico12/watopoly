#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>

const int MAX_UPGRADES = 5;  // define max_upgrades here as a constant variable
class Property {
  std::string block;  // may need block.cc/block.h

  int purchaseCost, impCost;

 public:
  int getLvl();
  bool isMaxUpgrade();
  int getPurCost();
  int getImpCost();
  bool upgrade();
};

#endif