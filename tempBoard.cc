#include "tempboard.h"

#include <iostream>

const int BOARD_SIZE = 40;
const int linesPerBlock = 5;
const std::string vSeparator = "|";
const std::string hSeparator = {7, '_'};
const std::string blankSpace = {71, ' '};

Board::Board() : blocks(BOARD_SIZE) {}

void Board::setBlock(int index, Block block) {
  blocks[index] = block;
}

std::vector<Block>* Board::getBlocks() {
  return &blocks;
}

std::ostream& operator<<(std::ostream& os, const Board& board) {
  std::vector<Block> blocks = board.getBlocks();

  // Top row of blocks
  for (int i = -1; i <= linesPerBlock; i++) {
    for (int j = BOARD_SIZE / 2; j <= BOARD_SIZE / 2; j++) {
      os << vSeparator;
      if (0 <= i && i < linesPerBlock) {
        os << blocks[j].displayName[i];
      } else {
        os << hSeparator;
      }
    }
    os << vSeparator << std::endl;
  }

  // Middle rows of blocks
  for (int i = BOARD_SIZE / 2; i < BOARD_SIZE / 4; i++) {
    for (int j = 0; j <= linesPerBlock; j++) {
      os << vSeparator;
      if (j != linesPerBlock) {
        os << blocks[i].displayName[j];
      } else {
        os << hSeparator;
      }

      os << vSeparator;
      os << blankSpace;
      os << vSeparator;

      if (j != linesPerBlock) {
        os << blocks[BOARD_SIZE * 5 / 4 - i].displayName[j];
      } else {
        os << hSeparator;
      }
      os << vSeparator;
    }
  }

  for (int i = 0; i < linesPerBlock; i++) {
    os << blocks[BOARD_SIZE / 4 + 1].displayName[i];

    os << vSeparator;
    os << blankSpace;
    os << vSeparator;

    os << blocks[BOARD_SIZE - 1].displayName[i];
    os << vSeparator;
  }

  // Bottom row of blocks
  for (int i = -1; i <= linesPerBlock; i++) {
    for (int j = BOARD_SIZE / 4; j >= 0; j--) {
      os << vSeparator;
      if (0 <= i && i < linesPerBlock) {
        os << blocks[j].displayName[i];
      } else {
        os << hSeparator;
      }
    }
    os << vSeparator << std::endl;
  }

  return os;
}