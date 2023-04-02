#ifndef BLOCK_H
#define BLOCK_H

#include <string>

extern const std::string EMPTY_LINE;

class Block {
 protected:
  bool occupiable;
  std::string name;
  bool canOwn;
  std::string ownedBy;
  static const int displayLength = 5;
  std::string displayName[displayLength];  // For visual display

 public:
  Block(std::string name, bool ownable, std::string owner);
  std::string getName();
  std::string getOwner();
  std::string *getDisplayName();
};

#endif
