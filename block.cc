#include "block.h"

const std::string EMPTY_LINE{7, ' '};

Block::Block(std::string name) : name{name}, canOwn{ownable}, owner{owner} {
  for (int i = 0; i < displayLength; i++) {
    displayName[i] = EMPTY_LINE;
  }
}

std::string Block::getName() {
  return name;
}

std::string Block::getOwner() {
  return owner;
}

std::string *Block::getDisplayName() {
  return displayName;
}
