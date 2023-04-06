#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>
#include <vector>

#include "../block.h"
#include "../info.h"
#include "../state.h"

class Property : public Block {
 protected:
  int purchaseCost, improvLvl;
  bool mortgaged = false;

 public:
  Property(std::string name, int purchaseCost, int improvLvl);
  int getLvl();
  int getPurCost();
  bool isMortgaged();
  void toggleMortgage();
  virtual bool upgrade() = 0;
  virtual int getFee() = 0;
};

#endif
