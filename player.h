#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

#include "Property/academic.h"
#include "Property/property.h"
#include "info.h"
#include "state.h"
#include "token.h"
// #include "Property/nonacademic.h"

extern const int BOARD_SIZE;
extern const int COLLECT_OSAP;
extern const int DC_TIMS_LINE;

class Player {
  std::string name;
  Token token;
  int money, position;
  std::vector<Property *> props;
  int timsCups;
  int timsRounds;

 public:
  Player(std::string name, Token token,
         int money = 0, int position = 0,
         std::vector<Property *> props = {},
         int timsCups = 0);

  // Player(const Player &o);

  // Player(Player &&o);

  std::string getName();

  Property *getProperty(std::string propertyName);

  char getCharToken();

  int getPosition();

  int getMoney();

  int getTimsCups();

  void addTimsCup();

  void useTimsCup();

  void setPosition(int n);

  std::vector<Property *> getProperties();

  void move(int n);

  void moveTo(int n, bool collect = true);

  bool hasMoney(int amount);

  void addMoney(int amount);

  void removeMoney(int amount);

  int hasProperty(Property &prop);

  void addProperty(Property &prop);

  bool removeProperty(Property &prop);

  bool buy(Property &prop);

  bool improve(Property &prop);

  bool trade(Player &p2, Property &prop1, Property &prop2);
  bool trade(Player &p2, int amount, Property &prop2);
  bool trade(Player &p2, Property &prop1, int amount);

  int getTimsRounds();

  void spentRoundInTims(bool outOfTims = false);

  void reset();
};

#endif
