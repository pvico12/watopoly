#include "block.h"

#include <sstream>

#include "info.h"
#include "state.h"

const std::string EMPTYLINE(7, ' ');

Block::Block(std::string name) : name{name} {
  // initialize display
  for (int i = 0; i < displayLength; i++) {
    displayName[i] = EMPTYLINE;
  }

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

  // insert the lines into the displayName
  int i = 0;
  for (auto s : displayComponents) {
    s.resize(7, ' ');
    displayName[i] = s;
    i++;
  }

  info = BlockInfo{name, 0, BlockDesc::Other};
  state = BlockState{BlockStateType::NewVisitor, BlockDesc::Other};
  setInfo(info);
  setState(state);
  notifyObservers();
}

std::string Block::getName() {
  return name;
}

std::string *Block::getDisplayName() {
  return displayName;
}