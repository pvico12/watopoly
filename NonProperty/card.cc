#include "card.h"

CardBlock::CardBlock(std::string name, int numCards)
    : NonProperty{name},
      numCards{numCards},
      cards(numCards),
      cumulativeChances(std::vector<double>(numCards)) {
  double defaultChance = 1.0 / numCards;
  double cumulativeChance = 0.0;
  for (int i = 0; i < numCards; i++) {
    cards[i].chance = defaultChance;
    cumulativeChance += defaultChance;
    cumulativeChances[i] = cumulativeChance;
  }
}

CardBlock::CardBlock(std::string name, int numCards, std::vector<Card> cards)
    : NonProperty{name},
      numCards{numCards},
      cards{cards},
      cumulativeChances(std::vector<double>(numCards)) {
  double cumulativeChance = 0.0;
  for (int i = 0; i < numCards; i++) {
    cumulativeChance += cards.at(i).chance;
    cumulativeChances[i] = cumulativeChance;
  }
}

bool CardBlock::setCards(const std::vector<Card>& newCards) {
  if (newCards.size() != numCards) {
    return false;
  }

  double total = 0;
  for (const auto& card : newCards) {
    total += card.chance;
  }

  if (total != 1) {
    return false;
  }

  double cumulativeChance = 0;
  for (int i = 0; i < numCards; i++) {
    cards[i] = newCards[i];
    cumulativeChance += newCards[i].chance;
    cumulativeChances[i] = cumulativeChance;
  }
  return true;
}

void CardBlock::action(Player& player) {
  double randomValue = static_cast<double>(rand()) / RAND_MAX;
  for (int i = 0; i < numCards; i++) {
    if (randomValue <= cumulativeChances[i]) {
      cards[i].action(player);
      break;
    }
  }
}