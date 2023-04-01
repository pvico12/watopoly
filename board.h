#ifndef BOARD_H
#define BOARD_H

#include <vector>

#include "block.h"

extern const int BOARD_SIZE;

class Board {
  std::vector<Block> blocks;

 public:
  Board();
  void setBlock(int index, Block block);
  std::vector<Block> *getBlocks();
};

#endif