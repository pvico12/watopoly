#include "player.h"

const int BOARD_SIZE = 40;  // temporarily here before structure is determined

Player::Player(std::string name, Token token, int position = 0, int money = 0, std::vector<Property> properties = {})
    : name{name}, token{token}, position{position}, money{money}, properties{properties} {}

void Player::move(int n) {
  // need to add $200 when passing through Collect OSAP
  position = (position + n) % 40;
}

bool Player::hasMoney(int amount) {
  return money >= amount;
}

void Player::addMoney(int amount) {
  money += amount;
}

bool Player::removeMoney(int amount) {
  if (!hasMoney(amount)) {
    return false;
  }
  money -= amount;
  return true;
}

int Player::hasProperty(Property &prop) {
  // to be implemented
  return -1;
}

void Player::addProperty(Property &prop) {
  properties.emplace_back(prop);
}

bool Player::removeProperty(Property &prop) {
  int index = hasProperty(prop);
  if (index == -1) {
    return false;
  }
  properties.erase(properties.begin() + index);
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

bool Player::trade(Player &p2, Property &prop1, Property &prop2) {
  if (hasProperty(prop1) && p2.hasProperty(prop2)) {
    removeProperty(prop1);
    p2.removeProperty(prop2);
    addProperty(prop2);
    p2.addProperty(prop1);
    return true;
  }
  return false;
}

bool Player::trade(Player &p2, int amount, Property &prop2) {
  if (hasMoney(amount) && p2.hasProperty(prop2)) {
    removeMoney(amount);
    p2.removeProperty(prop2);
    addProperty(prop2);
    p2.addMoney(amount);
    return true;
  }
  return false;
}

bool Player::trade(Player &p2, Property &prop1, int amount) {
  if (hasProperty(prop1) && p2.hasMoney(amount)) {
    removeProperty(prop1);
    p2.removeMoney(amount);
    addMoney(amount);
    p2.addProperty(prop1);
    return true;
  }
  return false;
}