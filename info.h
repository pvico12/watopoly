#ifndef INFO_H
#define INFO_H
#include <string>

#include "state.h"

struct BlockInfo {
  std::string name;
  int position;
  BlockDesc desc;

  BlockInfo();
  BlockInfo(std::string name, int position);
  BlockInfo(std::string name, int position, BlockDesc desc);
};

#endif