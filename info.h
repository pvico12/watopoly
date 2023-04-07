#ifndef INFO_H
#define INFO_H
#include <string>

#include "state.h"

struct BlockInfo {
  std::string name;
  int position;
  BlockDesc desc;
  Player *owner = nullptr;

  BlockInfo();
  BlockInfo(std::string name, int position);
  BlockInfo(std::string name, int position, BlockDesc desc);

  BlockInfo(const BlockInfo &o);

  void setOwner(Player *p);
};

#endif