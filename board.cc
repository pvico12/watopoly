#include "board.h"

const int BOARD_SIZE = 40;

Board::Board() : blocks(BOARD_SIZE) {}

void Board::setBlock(int index, Block block) {
  blocks[index] = block;
}

std::vector<Block> *Board::getBlocks() {
  return &blocks;
}