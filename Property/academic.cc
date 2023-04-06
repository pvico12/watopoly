#include "../block.h"
#include "academic.h"
#include "../info.h"
#include "../state.h"
#include <sstream>

const int MAXUPGRADES = 5;
const std::string DASHEDLINE(7, '-');

Academic::Academic(std::string name, std::string monBlock, int purchaseCost, int improvLvl, std::vector<int> tuition, int improvCost)
    : Property{name, purchaseCost, improvLvl},improvCost{improvCost},monopolyBlock{monBlock}, tuition{tuition} {

  displayName[0] = EMPTYLINE;
  displayName[1] = DASHEDLINE;

  // partition name accordingly
  std::vector<std::string> nameComponents;
  std::istringstream iss{name};
  std::string component;
  // create vector of space seperated strings
  while (std::getline(iss, component, ' ')) {
    nameComponents.emplace_back(component);
  }

  // see if any two strings can fit in one line and append them
  std::vector<std::string> displayComponents;
  std::string line;
  for (auto s : nameComponents) {
    if (line.length() + s.size() > 7) {
      displayComponents.emplace_back(line);
      line = "";
    }
    line.append(s + " ");
  }
  displayComponents.emplace_back(line);

  // finsert the lines into the displayName
  int i = 2;
  for (auto s : displayComponents) {
    s.resize(7, ' ');
    displayName[i] = s;
    i++;
  }
}

int Academic::getImpCost() {
  return improvCost;
}

std::string Academic::getMonBlock() {
	return monopolyBlock;
}

bool Academic::upgrade() {
  if (improvLvl >= MAXUPGRADES) {
    return false;
  }

  improvLvl++;
  return true;
}

bool Academic::isMaxUpgrade() {
  return improvLvl >= MAXUPGRADES;
}

int Academic::getFee() {
  return tuition.at(improvLvl);
}