#ifndef INFO_H
#define INFO_H
#include <string>

#include "state.h"

struct BlockInfo {
  std::string name = "";
  int position = 0;
  BlockDesc desc = BlockDesc::Other;
  Player *owner = nullptr;
  int impLevel = 0;

  BlockInfo();
  BlockInfo(std::string name, int position);
};

#endif