#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

#include "Property/academic.h"
#include "Property/property.h"

extern const int BOARD_SIZE;

class Player {
  std::string name;
  int position, money;
  std::vector<Property> properties;

 public:
  Player(std::string name, int position = 0, int money = 0, std::vector<Property> properties = {});

  void move(int n);  // may put it in board instead of here

  void add(int amount);

  bool remove(int amount);  // may change to void

  bool buy(Property &prop);

  bool improve(Academic &prop);

  bool trade(Player &p);  // may need to add additional parameters
};

#endif