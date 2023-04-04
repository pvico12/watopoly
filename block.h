#ifndef BLOCK_H
#define BLOCK_H

#include <string>

#include "subject.h"

extern const std::string EMPTY_LINE;

class Block : public Subject {
 protected:
  std::string name;
  //std::string type;
  static const int displayLength = 5;
  std::string displayName[displayLength];  // For visual display
 public:
  Block(std::string name);
  std::string getName();
	//virtual std::string getType() = 0; // PVM: now an Abstract Class
  std::string *getDisplayName(); // depends on property/non property
};

#endif
