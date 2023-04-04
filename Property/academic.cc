#include "academic.h"

extern const int MAX_UPGRADES;
extern const std::string DASHED_LINE(7, '-');

Academic::Academic(std::string name, std::string monBlock, int purchaseCost, int improvLvl, std::vector<int> tuition, int improvCost)
    : Property{name, purchaseCost, improvLvl},
      improvCost{improvCost},
			monopolyBlock{monBlock},
			tuition{tuition} {
  displayName[1] = DASHED_LINE;
  name.resize(7, ' ');
  displayName[2] = name;
}

int Academic::getImpCost() {
  return improvCost;
}

std::string Academic::getMonBlock() {
	return monopolyBlock;
}

bool Academic::upgrade() {
  if (improvLvl >= 5 /*MAX_UPGRADES, had to change temporarily for compilation, fix it*/) {
    return false;
  }

  improvLvl++;
  return true;
}

bool Academic::isMaxUpgrade() {
  return improvLvl >= 5 /* same thing^^ */;
}

int Academic::getFee() {
  return tuition.at(improvLvl);
}
