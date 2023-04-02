#ifndef BLOCK_H
#define BLOCK_H

#include <string>

extern const std::string EMPTY_LINE;

class Block {
 protected:
  std::string name;
  static const int displayLength = 5;
  std::string displayName[displayLength];  // For visual display

 public:
  Block(std::string name);
  std::string getName();
  std::string *getDisplayName();
};

#endif