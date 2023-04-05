#ifndef INFO_H
#define INFO_H
#include "state.h"
#include <string>

struct Info {
  std::string name;
  int position;
  Desc desc; // descriptor of type of block
};

#endif