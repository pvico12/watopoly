#ifndef BLOCK_H
#define BLOCK_H

#include <string>

class Block {
 protected:
  std::string name;
  std::string displayName[5]; // For visual display

 public:
  std::string getName();
  virtual std::string *getDisplayName();
};

#endif