#include "property.h"

Property::Property(int improvLvl = 0, int purchaseCost, int improvCost)
    : improvLvl{improvLvl},
      purchaseCost{purchaseCost},
      improvCost{improvCost} {
  // ADD
}

int Property::getLvl() {
  return improvLvl;
}

int Property::getPurCost() {
  return purchaseCost;
}

int Property::getImpCost() {
  return improvCost;
}

bool Property::upgrade() {
  if (improvLvl >= MAX_UPGRADES) {
    return false;
  }

  improvLvl++;
  return true;
}