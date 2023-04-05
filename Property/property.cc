#include "property.h"

Property::Property(std::string name, int purchaseCost, int improvLvl)
    : Block{name}, purchaseCost{purchaseCost}, improvLvl{improvLvl} {}

int Property::getLvl() {
  return improvLvl;
}

int Property::getPurCost() {
  return purchaseCost;
}
