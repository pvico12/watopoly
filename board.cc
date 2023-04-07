#include "board.h"
#include "subject.h"
#include "Property/academic.h"
#include "Property/nonacademic.h"
#include "NonProperty/movement.h"
#include "NonProperty/money.h"
#include "info.h"
#include "state.h"
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

		std::string type = blockParams[0];
		std::string name = blockParams[1];;
		BlockInfo newI{name, currPos};

		if (type == "Academic") {
			int purchaseCost = std::stoi(blockParams[3]);
			int improvLevel = std::stoi(blockParams[4]);
			int improvCost = std::stoi(blockParams[6]);;
			std::vector<int> numArr; // fix
			newI.desc = BlockDesc::AcademicBuilding;
			b = new Academic(name, blockParams[3], purchaseCost, improvLevel, numArr, improvCost);
		} else if (type == "NonAcademic") {
			int purchaseCost = std::stoi(blockParams[2]);
			int improvLevel = std::stoi(blockParams[3]);
			newI.desc = BlockDesc::NonAcademicBuilding;
			b = new NonAcademic(name, purchaseCost, improvLevel, Type::Gym);
		} else if (type == "MoneyBlock") {
			int money = std::stoi(blockParams[2]);
			MoneyType mt = MoneyType::ADD;
			newI.desc = BlockDesc::ChancePay;
			b = new MoneyBlock(name, money, mt);
		} else if (type == "MovementBlock") {
			int move = std::stoi(blockParams[2]);
			MoveType mt = MoveType::MOVE_N_STEPS;
			newI.desc = BlockDesc::ChanceMove;
			b = new MovementBlock(name, move, mt);
		} else if (type == "NonProperty") {
			newI.desc = BlockDesc::Other;
			b = new MoneyBlock(name, 0, MoneyType::ADD);
		}

		b->setInfo(newI);
		b->notifyObservers();
		blocks.emplace_back(b); // add to end of block list

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
	out << *(b.td);
	return out;
}