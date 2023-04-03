#ifndef BLOCK_H
#define BLOCK_H

#include <string>

extern const std::string EMPTY_LINE;

class Block : public Subject {
 protected:
  std::string name;
  std::string type;
	bool canOwn;
  static const int displayLength = 5;
  std::string displayName[displayLength];  // For visual display
 public:
  Block(std::string name, bool ownable);
  std::string getName();
	virtual std::string getType() = 0; // PVM: now an Abstract Class
  virtual std::string *getDisplayName() = 0; // depends on property/non property
};

#endif
