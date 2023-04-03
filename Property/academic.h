#ifndef ACADEMIC_H
#define ACADEMIC_H

#include <string>
#include <vector>

#include "property.h"

extern const int MAX_UPGRADES;
extern const std::string DASHED_LINE;

class Academic : public Property {
  int improvCost;
  std::vector<int> tuition;

 public:
  Academic(std::string name, int purchaseCost, int improvLvl, std::vector<int> fees, int improvCost);
  int getImpCost();
  bool upgrade();
  bool isMaxUpgrade();
  int getFee();
};

#endif