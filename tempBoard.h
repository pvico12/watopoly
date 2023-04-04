#ifndef TEMPBOARD_H
#define TEMPBOARD_H

#include <vector>

#include "block.h"

extern const int BOARD_SIZE;

class Board {
  std::vector<Block> blocks;

 public:
  Board();
  void setBlock(int index, Block block);
  std::vector<Block> *getBlocks();
  friend std::ostream& operator<<(std::ostream& os, const Board& board);
};

#endif