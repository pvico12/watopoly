#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>

#include "block.h"
#include "textdisplay.h"

extern const int BOARD_SIZE;

class Board {
  std::vector<Block*> blocks;
  int timsCupCount = 0;
  TextDisplay *td = nullptr;
 public:
  Board();
  Board(TextDisplay &td);
  int getCupCount();
  void setCupCount(int count);
  std::vector<Block*> *getBlocks();
  friend std::ostream &operator<<(std::ostream &out, const Board &b);
};

#endif