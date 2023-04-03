#include "player.h"

const int BOARD_SIZE = 40;  // temporarily here before structure is determined

Player::Player(std::string name, Token token, int position = 0, int money = 0, std::vector<Property> properties = {})
    : name{name}, token{token}, position{position}, money{money}, properties{properties} {}

void Player::move(int n) {
  // need to add $200 when passing through Collect OSAP
  position = (position + n) % 40;
}

void Player::addMoney(int amount) {
  money += amount;
}

bool Player::removeMoney(int amount) {
  if (money < amount) {
    // add print
    return false;
  }
  money -= amount;
  return true;
}

void Player::addProperty(Property &prop) {
  properties.emplace_back(prop);
}

bool Player::removeProperty(Property &prop) {
  // to be implemented
  return false;
}

bool Player::buy(Property &prop) {
  if (money < prop.getPurCost()) {
    // add print
    return false;
  }
  money -= prop.getPurCost();
  properties.emplace_back(prop);
}

bool Player::improve(Academic &prop) {
  if (money < prop.getImpCost() && !prop.isMaxUpgrade()) {
    // add print
    return false;
  }
  money -= prop.getImpCost();
  prop.upgrade();
}

bool trade(Player &p);  // to be implemented