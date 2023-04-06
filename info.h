#ifndef INFO_H
#define INFO_H
#include "state.h"

#include <string>
#include <vector>

struct PlayerInfo {
  std::string name;
  char nickname;
  int position;
};

struct BlockInfo {
  std::string name;
  int position;
  BlockDesc desc;
};

#endif