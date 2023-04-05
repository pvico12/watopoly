#include "property.h"

Property::Property(std::string name, bool canImprove, int purchaseCost, int improvLvl)
    : Block{name, canImprove}, purchaseCost{purchaseCost}, improvLvl{improvLvl} {}

int Property::getLvl() {
  return improvLvl;
}

int Property::getPurCost() {
  return purchaseCost;
}
