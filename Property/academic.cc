#include "academic.h"

extern const int MAX_UPGRADES = 5;

Academic::Academic(std::string name, std::string monBlock, int purchaseCost, int improvLvl, std::vector<int> tuition, int improvCost)
    : Property{name, true, purchaseCost, improvLvl},
      improvCost{improvCost},
			monopolyBlock{monBlock},
			tuition{tuition} {}

int Academic::getImpCost() {
  return improvCost;
}

std::string Academic::getMonBlock() {
	return monopolyBlock;
}

bool Academic::upgrade() {
  if (improvLvl >= MAX_UPGRADES) {
    return false;
  }

  improvLvl++;
  return true;
}

bool Academic::isMaxUpgrade() {
  return improvLvl >= MAX_UPGRADES;
}

int Academic::getFee() {
  return tuition.at(improvLvl);
}
