#ifndef BLOCK_H
#define BLOCK_H

#include "state.h"
#include "info.h"
#include "subject.h"
#include <string>

extern const std::string EMPTYLINE;

class Block : public Subject<BlockInfo, BlockState> {
 protected:
  std::string name;
  static const int displayLength = 5;
  std::string displayName[displayLength];  // For visual display
  BlockInfo info;
  BlockState state;
 public:
  // need to be declared before constructor because it uses these methods
  BlockInfo getInfo();
  BlockState getState();
  void setInfo(BlockInfo newI);
  void setState(BlockState newS);
  Block(std::string name);
  std::string getName();
  std::string *getDisplayName(); // depends on property/non property
};

#endif
