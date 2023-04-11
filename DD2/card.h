#ifndef CARDBLOCK_H
#define CARDBLOCK_H

#include "nonproperty.h"
#include "player.h"
#include <functional>

struct Card {
  std::function<void(Player&)> action;
  double chance;
};

class CardBlock : public NonProperty {
  int numCards;
  std::vector<Card> cards;
  std::vector<double> cumulativeChances;

 public:
  CardBlock(std::string name, int totalCards);
  CardBlock(std::string name, int totalCards, std::vector<Card> cards);
  bool setCards(const std::vector<Card>& newCards);
  virtual void action(Player &player);
};

#endif
