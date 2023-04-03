#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

#include "Property/academic.h"
#include "Property/property.h"

extern const int BOARD_SIZE;

enum class Token {
  GOOSE,
  GRT_BUS,
  TIM_HORTONS,
  DOUGHNUT,
  PROFESSOR,
  STUDENT,
  MONEY,
  LAPTOP,
  PINK_TIE
};

class Player {
  std::string name;
  Token token;
  int position, money;
  std::vector<Property> properties;

 public:
  Player(std::string name, Token token, int position = 0, int money = 0, std::vector<Property> properties = {});

  void move(int n);  // may put it in board instead of here

  void add(int amount);

  bool remove(int amount);  // may change to void

  bool buy(Property &prop);

  bool improve(Academic &prop);

  bool trade(Player &p);  // may need to add additional parameters
};

#endif