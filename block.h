#ifndef BLOCK_H
#define BLOCK_H

#include <string>

#include "subject.h"

extern const std::string EMPTYLINE;
extern const std::string DASHEDLINE;

class Block : public Subject {
 protected:
  std::string name;
  static const int displayLength = 5;
  std::string displayName[displayLength];  // For visual display
 public:
  Block(std::string name, bool canImprove);
  std::string getName();
  std::string *getDisplayName(); // depends on property/non property
};

#endif
