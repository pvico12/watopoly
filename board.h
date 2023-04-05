#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>

#include "block.h"
#include "textdisplay.h"

extern const int BOARD_SIZE;

class Board {
  std::vector<Block*> blocks;
	int timsCupCount;
  TextDisplay *td = nullptr;
 public:
	Board(TextDisplay &td);
	int getCupCount();
  std::vector<Block*> *getBlocks();
	friend std::ostream &operator<<(std::ostream &out, const Board &b);
};

#endif