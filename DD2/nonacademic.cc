#include "nonacademic.h"

NonAcademic::NonAcademic(std::string name, int purchaseCost, int improvLvl, Type type)
    : Property{name, purchaseCost, improvLvl}, type{type} {}

Type NonAcademic::getType() {
  return type;
}

bool NonAcademic::upgrade() {
  // called when a player purchases a new non-academic building
  // when the player already owns an academic building of the same type
  improvLvl++;
	return true; // change
}

int NonAcademic::getFee() {
  if (type == Residence) {
    int amount = 25;
    for (int i = 2; i <= improvLvl; i++) {
      amount *= 2;
    }
    return amount;
  } else if (type == Gym) {
    // sum = roll two dice
    // - lvl 1: 4 * sum
    // - lvl 2: 10 * sum
    // this is dealt with in commandInterpreter.cc
    return 0;
  } else {
    return 0;
  }
}
