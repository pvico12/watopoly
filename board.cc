#include "board.h"

const int BOARD_SIZE = 40;

Board::Board(std::vector<Block> blocks, TextDisplay &td) : blocks{blocks}, timsCupCount{0}, td{&td} {}

int Board::getCupCount() {
	return timsCupCount;
}

void Board::setBlock(int index, Block block) {
  blocks[index] = block;
}

std::vector<Block> *Board::getBlocks() {
  return &blocks;
}

std::ostream &operator<<(std::ostream &out, const Board &b) {
	out << b.td;
	return out;
}
