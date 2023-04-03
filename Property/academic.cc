#include "academic.h"

extern const int MAX_UPGRADES;
extern const std::string DASHED_LINE{7, '-'};

Academic::Academic(std::string name, int purchaseCost, int improvLvl, std::vector<int> tuition, int improvCost)
    : Property{name, purchaseCost, improvLvl},
      tuition{tuition},
      improvCost{improvCost} {
  displayName[1] = DASHED_LINE;
  name.resize(7, ' ');
  displayName[2] = name;
}

int Academic::getImpCost() {
  return improvCost;
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