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

  bool hasMoney(int amount);

  void addMoney(int amount);

  bool removeMoney(int amount);  // may change to void

  int hasProperty(Property &prop);

  void addProperty(Property &prop);
  
  bool removeProperty(Property &prop);

  bool buy(Property &prop);

  bool improve(Academic &prop);

  bool trade(Player &p2, Property &prop1, Property &prop2);
  bool trade(Player &p2, int amount, Property &prop2);
  bool trade(Player &p2, Property &prop1, int amount);
};

#endif
