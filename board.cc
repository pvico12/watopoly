#include "board.h"
#include "subject.h"
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
	int currPos = 0;
	Block *b;
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
			Info newI;
			newI.name = blockParams[2];
			newI.position = currPos;
			newI.desc = Desc::AcademicBuilding;
			b = new Academic(blockParams[2], blockParams[3], purchaseCost, improvLevel, numArr, improvCost);
			b->setInfo(newI);
			blocks.emplace_back(b); // add to end of block list
		} else {
			int purchaseCost = std::stoi(blockParams[3]);
			int improvLevel = std::stoi(blockParams[4]);
			Info newI;
			newI.name = blockParams[2];
			newI.position = currPos;
			newI.desc = Desc::AcademicBuilding;
			b = new NonAcademic(blockParams[2], purchaseCost, improvLevel, Type::Gym);
			b->setInfo(newI);
			blocks.emplace_back(b); // add to end of block list
		}
		currPos++;
	}

	td.initDisplay(blocks); // initialize textDisplay

	// set up observers
	for (auto block : blocks) {
		block->attach(&td);
	}
}

int Board::getCupCount() {
	return timsCupCount;
}

std::vector<Block*> *Board::getBlocks() {
  return &blocks;
}

std::ostream &operator<<(std::ostream &out, const Board &b) {
	out << b.td;
	return out;
}