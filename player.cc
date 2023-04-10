#include "player.h"

#include <iostream>

#include "info.h"
#include "state.h"

const int COLLECT_OSAP = 20;
const int DC_TIMS_LINE = 30;

Player::Player(std::string name, Token token, int money, int position,
               std::vector<Property *> props, int timsCups)
    : name{name},
      token{token},
      money{money},
      position{position},
      props{props},
      timsCups{timsCups},
      timsRounds{0} {}

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
  return tokenToCharMap[token];
}

int Player::getPosition() {
  return position;
}

int Player::getMoney() {
  return money;
}

int Player::getTimsCups() {
  return timsCups;
}

void Player::addTimsCup() {
  timsCups++;
}

void Player::useTimsCup() {
  timsCups--;
}

void Player::setPosition(int n) {
  position = n;
}

std::vector<Property *> Player::getProperties() {
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
  if (timsRounds != 0) {
    std::cout << "You are currently in DC Tims Line." << std::endl;
    std::cout << "You have " << std::to_string(timsRounds) << " rounds left in Tims." << std::endl;
    return;
  }

  position = (position + n) % 40;
  // if (position - n < 0) {
  //   money += 200;
  // }
  if (position > 20 && position - n < 20) {
    money += 200;
  }

  if (n > 0) {
    std::cout << "You have moved " << std::to_string(n) << " steps forwards." << std::endl;
  } else if (n < 0) {
    std::cout << "You have moved " << std::to_string(-n) << " steps backwards." << std::endl;
  } else {
    std::cout << "You remain in your current position." << std::endl;
  }
}

void Player::moveTo(int n, bool collect) {
  // if (collect && position < n) {
  //   money += 200;
  // }
  if (collect && position < 20 && n >= 20) {
    money += 200;
  }
  position = n;

  if (n == COLLECT_OSAP) {
    std::cout << "You have been moved to Collect OSAP." << std::endl;
    if (collect) {
      std::cout << "$200 has been added to your account." << std::endl;
    }
  } else if (n == DC_TIMS_LINE) {
    std::cout << "You have been moved to DC Tims Line." << std::endl;
    timsRounds = 3;
  } else {
    std::cout << "You have moved to block " + std::to_string(n) + "." << std::endl;
  }
}

bool Player::hasMoney(int amount) {
  return money >= amount;
}

void Player::addMoney(int amount) {
  money += amount;
  std::cout << "$" << std::to_string(amount) << " has been added to " << name << "'s account." << std::endl;
}

void Player::removeMoney(int amount) {
  money -= amount;
  std::cout << "$" << std::to_string(amount) << " has been removed from " << name << "'s account." << std::endl;
  if (money < 0) {
    std::cout << "your account total is now -$" << std::to_string(-money) << "." << std::endl;
    std::cout << "Would you like to mortgage or trade with other players to prevent bankruptcy?" << std::endl;
  }
}

int Player::hasProperty(Property &prop) {
  // wack implementation of hasProperty()
  int len = props.size();
  for (int i = 0; i < len; i++) {
    if (props.at(i)->getName() == prop.getName()) {
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
  Academic *academic = dynamic_cast<Academic *>(&prop);
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

bool Player::worsen(Property &prop) {
  Academic *academic = dynamic_cast<Academic *>(&prop);
  if (academic == nullptr) {
    return false;
  }
  if (money < academic->getImpCost() && academic->isMaxUpgrade()) {
    // add print
    return false;
  }
  money += (academic->getImpCost() / 2);
  academic->worsen();
  return true;
}

bool Player::trade(Player &p2, Property &prop1, Property &prop2) {
  if (hasProperty(prop1) == -1) {
    return false;
  }
  if (p2.hasProperty(prop2) == -1) {
    return false;
  }
  removeProperty(prop1);
  p2.removeProperty(prop2);
  addProperty(prop2);
  p2.addProperty(prop1);
  return true;
}

bool Player::trade(Player &p2, int amount, Property &prop2) {
  if (!hasMoney(amount)) {
    return false;
  }
  if (p2.hasProperty(prop2) == -1) {
    return false;
  }
  removeMoney(amount);
  p2.removeProperty(prop2);
  addProperty(prop2);
  p2.addMoney(amount);
  return true;
}

bool Player::trade(Player &p2, Property &prop1, int amount) {
  if (hasProperty(prop1) == -1) {
    return false;
  }
  if (!p2.hasMoney(amount)) {
    return false;
  }
  removeProperty(prop1);
  p2.removeMoney(amount);
  addMoney(amount);
  p2.addProperty(prop1);
  return true;
}

int Player::getTimsRounds() {
  return timsRounds;
}

void Player::spentRoundInTims(bool outOfTims) {
  if (outOfTims) {
    timsRounds = 0;
  } else {
    timsRounds--;
  }
}

void Player::reset() {
  int numProps = props.size();
  for (int i = 0; i < numProps; i++) {
    props.at(i)->reset();
  }
  props.clear();
  timsCups = 0;
}