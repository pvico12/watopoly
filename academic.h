#ifndef ACADEMIC_H
#define ACADEMIC_H

#include <string>
#include <vector>

#include "property.h"

extern const int MAX_UPGRADES;
extern const std::string DASHED_LINE;

class Academic : public Property {
  int improvCost;
  std::string monopolyBlock;
	std::vector<int> tuition;

 public:
  Academic(std::string name, std::string monBlock, int purchaseCost, int improvLvl, std::vector<int> fees, int improvCost);
  int getImpCost();
	std::string getMonBlock();
  bool upgrade();
  bool isMaxUpgrade();
  int getFee();
};

#endif
