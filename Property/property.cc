#include "property.h"
#include "../block.h"

Property::Property(std::string name, int purchaseCost, int improvLvl)
    : Block{name}, purchaseCost{purchaseCost}, improvLvl{improvLvl} {}

int Property::getLvl() {
  return improvLvl;
}

int Property::getPurCost() {
  return purchaseCost;
}

bool Property::isMortgaged() {
  return mortgaged;
}

void Property::toggleMortgage() {
  mortgaged = !mortgaged;
}

void Property::reset() {
  improvLvl = 0;
  mortgaged = false;
}