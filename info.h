#ifndef INFO_H
#define INFO_H
#include "state.h"
#include <string>

struct BlockInfo {
  std::string name;
  int position;
  BlockDesc desc;
};

#endif