#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "property.h"

// forward declaration of property
// may change it to include
// class Property;

class Player {
  std::string name;
  int total;
  std::vector<Property> properties;

 public:
  void move(int n);  // may put it in board instead of here

  void add(int amount);

  bool remove(int amount); // may change to void

  bool buy(Property &prop);

  bool improve(Property &prop);

  bool trade(Player &p);  // may need to add additional parameters
};

#endif