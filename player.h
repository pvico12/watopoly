#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

#include "token.h"
#include "info.h"
#include "state.h"
#include "Property/property.h"
#include "Property/academic.h"
//#include "Property/nonacademic.h"

extern const int BOARD_SIZE;

class Player {
  std::string name;
  Token token;
  int position, money;
  int timsCups = 0;
  std::vector<Property*> props;

 public:
  Player(std::string name, Token token,
        int position = 0, int money = 0,
        std::vector<Property*> props = {},
        int timsCups = 0);

  //Player(const Player &o);
  
  //Player(Player &&o);

  std::string getName();

  Property *getProperty(std::string propertyName);

  char getCharToken();

  int getPosition();

  int getMoney();

  int getTimsCups();

  void setPosition(int n);

  std::vector<Property*> getProperties();
  
  void move(int n);

  void moveTo(int n);

  bool hasMoney(int amount);

  void addMoney(int amount);

  bool removeMoney(int amount);  // may change to void

  int hasProperty(Property &prop);

  void addProperty(Property &prop);

  bool removeProperty(Property &prop);

  bool buy(Property &prop);

  bool improve(Property &prop);

  bool trade(Player &p2, Property &prop1, Property &prop2);
  bool trade(Player &p2, int amount, Property &prop2);
  bool trade(Player &p2, Property &prop1, int amount);
};

#endif
