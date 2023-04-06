#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

#include "info.h"
#include "state.h"
#include "Property/academic.h"
#include "Property/nonacademic.h"

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
  char tokenChar;
  Token token;
  int position, money;
  std::vector<Academic> academicProps;
  std::vector<NonAcademic> nonAcademicProps;

 public:
  Player(std::string name, char tokenChar, Token token,
        int position = 0, int money = 0,
        std::vector<Academic> academicProps = {},
        std::vector<NonAcademic> nonAcademicProps = {});

  Player(const Player &o);
  
  Player(Player &&o);

  std::string getName();

  Property *getProperty(std::string propertyName);

  char getCharToken();

  int getPosition();

  void setPosition(int n);

  std::vector<Academic> getAcademicProps();

  std::vector<NonAcademic> getNonAcademicProps();
  
  void move(int n);

  void moveTo(int n);

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
