#include "board.h"

const int BOARD_SIZE = 40;

Board::Board(TextDisplay &td) : blocks{BOARD_SIZE}, timsCupCount{0}, td{td} {}


int Board::getCupCount() {
	return timsCupCount;
}

void Board::setBlock(int index, Block block) {
  blocks[index] = block;
}

std::vector<Block> *Board::getBlocks() {
  return &blocks;
}
