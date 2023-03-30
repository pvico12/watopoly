#include "player.h"

void move(int n);

void Player::add(int amount) {
  total += amount;
}

bool Player::remove(int amount) {
  if (total < amount) {
    // add print
    return false;
  }
  total -= amount;
  return true;
}

bool Player::buy(Property &prop) {
  if (total < prop.getPurCost()) {
    // add print
    return false;
  }
  total -= prop.getPurCost();
  properties.emplace_back(prop);
}

bool Player::improve(Property &prop) {
  if (total < prop.getImpCost() && !prop.isMaxUpgrade()) {
    // add print
    return false;
  }
  total -= prop.getImpCost();
  prop.upgrade();
}

bool trade(Player &p); // to be implemented