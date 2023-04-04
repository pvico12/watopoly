#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>

#include "block.h"

class TextDisplay; // forward declaration

extern const int BOARD_SIZE;

class Board {
  std::vector<Block> blocks;
	int timsCupCount;
 public:
  TextDisplay *td = nullptr;
	Board(std::vector<Block> blocks, TextDisplay &td);
	int getCupCount();
  void setBlock(int index, Block block);
  std::vector<Block> *getBlocks();
	friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
