#ifndef NONACADEMIC_H
#define NONACADEMIC_H

#include "../info.h"
#include "../state.h"
#include "property.h"

enum Type {
  Residence,
  Gym
};

class NonAcademic : public Property {
  Type type;

 public:
  NonAcademic(std::string name, int purchaseCost, int improvLvl, Type type);
  bool upgrade();
  int getFee();
};

#endif