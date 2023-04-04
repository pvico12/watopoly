#include "board.h"
#include "Property/academic.h"
#include "Property/nonacademic.h"
#include <fstream>
#include <sstream>
#include <iostream>
const int BOARD_SIZE = 40;

Board::Board(TextDisplay &td) : timsCupCount{0}, td{&td}{
	// add all of these blocks to the array from block file
	std::ifstream file{"watopolyBlocks.txt"};
	std::string line;
	while(std::getline(file, line)) {
		std::istringstream iss(line);
		std::string param;
		std::vector<std::string> blockParams;

		while(std::getline(iss, param, '|')) {
				blockParams.emplace_back(param);
		}

		if (blockParams[0] == "Academic") {
			int purchaseCost = std::stoi(blockParams[4]);
			int improvLevel = std::stoi(blockParams[5]);
			int improvCost = std::stoi(blockParams[7]);;
			std::vector<int> numArr; // fix
			Academic tmpAcademic{blockParams[2], blockParams[3], purchaseCost, improvLevel, numArr, improvCost};
			blocks.emplace_back(tmpAcademic); // add to end of block list
		} else {
			int purchaseCost = std::stoi(blockParams[3]);
			int improvLevel = std::stoi(blockParams[4]);
			NonAcademic tmpNonAcademic{blockParams[2], purchaseCost, improvLevel, Type::Gym};
			blocks.emplace_back(tmpNonAcademic); // add to end of block list
		}
	}
	td.initDisplay(blocks);
}

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
