#include "property.h"

const std::string DASHED_LINE{7, '-'};

Property::Property(std::string name, std::vector<int> fees, int purchaseCost, int improvCost, int improvLvl)
    : Block{name},
      fees{fees},
      purchaseCost{purchaseCost},
      improvCost{improvCost},
      improvLvl{improvLvl} {
  displayName[1] = DASHED_LINE;
  name.resize(7, ' ');
  displayName[2] = name;
}

int Property::getLvl() {
  return improvLvl;
}

int Property::getPurCost() {
  return purchaseCost;
}

int Property::getImpCost() { // move to acadamic.cc
  return improvCost;
}

bool Property::upgrade() { // move to acadamic.cc
  if (improvLvl >= MAX_UPGRADES) {
    return false;
  }

  improvLvl++;
  return true;
}

bool Property::isMaxUpgrade() { // move to acadamic.cc
  return improvLvl >= MAX_UPGRADES;
}

int Property::getFee() { // differentiate between acadamic.cc and nonacadamic.cc
  return fees.at(improvLvl);
}