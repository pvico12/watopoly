#include "nonacademic.h"

NonAcademic::NonAcademic(std::string name, int purchaseCost, int improvLvl, Type type)
    : Property{name, purchaseCost, improvLvl}, type{type} {
  // change displayName accordingly
	name.resize(7, ' ');
	displayName[0] = name;
}

bool NonAcademic::upgrade() {
  // called when a player purchases a new non-academic building
  // when the player already owns an academic building of the same type
  improvLvl++;
	return true; // change
}

int NonAcademic::getFee() {
  if (type == Residence) {
    return 25 << improvLvl;
  } else if (type == Gym) {
    // sum = roll two dice
    // - lvl 1: 4 * sum
    // - lvl 2: 10 * sum
    return 0;
  } else {
		return 1; // change this
	}
}
