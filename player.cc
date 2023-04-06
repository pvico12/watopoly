#include "player.h"
#include "state.h"
#include "info.h"

Player::Player(std::string name, char tokenChar, Token token, int position, int money,
        std::vector<Property*> props)
    : name{name}, tokenChar{tokenChar}, token{token}, position{position}, money{money}, props{props} {}

/*
Player::Player(const Player &o)
  : name{o.name}, tokenChar{o.tokenChar}, token{o.token}, position{o.position}, money{o.money}, props{o.props} {}


Player::Player(Player &&o)
  : name{o.name}, tokenChar{o.tokenChar}, token{o.token}, position{o.position}, money{o.money}, props{o.props} {}
*/

std::string Player::getName() {
  return name;
};

char Player::getCharToken() {
  return tokenChar;
}

int Player::getPosition() {
  return position;
}

void Player::setPosition(int n) {
  position = n;
}

std::vector<Property*> Player::getProperties() {
  return props;
};

Property *Player::getProperty(std::string propertyName) {
  int len = props.size();
  for (int i = 0; i < len; i++) {
    if (props.at(i)->getName() == propertyName) {
      return props.at(i);
    }
  }
  return nullptr;
}

void Player::move(int n) {
  position = (position + n) % 40;
  if (position - n < 0) {
    money += 200;
  }
}

void Player::moveTo(int n) {
  position = n;
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
  // wack implementation of hasProperty()
  int len = props.size();
  for (int i = 0; i < len; i++) {
    if (props[i]->getName() == prop.getName()) {
      return i;
    }
  }
  return -1;
}

void Player::addProperty(Property &prop) {
  props.emplace_back(&prop);
}

bool Player::removeProperty(Property &prop) {
  int index = hasProperty(prop);
  if (index == -1) {
    return false;
  }
  props.erase(props.begin() + index);
  return true;
}

bool Player::buy(Property &prop) {
  if (money < prop.getPurCost()) {
    // add print
    return false;
  }
  money -= prop.getPurCost();
  props.emplace_back(&prop);
  return true;
}

bool Player::improve(Property &prop) {
  Academic *academic = dynamic_cast<Academic*>(&prop);
  if (academic == nullptr) {
    return false;
  }
  if (money < academic->getImpCost() && academic->isMaxUpgrade()) {
    // add print
    return false;
  }
  money -= academic->getImpCost();
  prop.upgrade();
  return true;
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