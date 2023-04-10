#include "board.h"
#include "subject.h"
#include "Property/academic.h"
#include "Property/nonacademic.h"
#include "NonProperty/movement.h"
#include "NonProperty/money.h"
#include "NonProperty/card.h"
#include "info.h"
#include "state.h"
#include <fstream>
#include <sstream>
#include <iostream>
const int BOARD_SIZE = 40;

Board::Board() : blocks{{}}, timsCupCount{0}, td{nullptr} {}

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
		BlockInfo info{name, currPos};

		if (type == "Academic") {
			int purchaseCost = std::stoi(blockParams[3]);
			int improvLevel = std::stoi(blockParams[4]);
			int improvCost = std::stoi(blockParams[6]);;
			
			// create tuition array
			std::string tuitions = blockParams[5];
			std::vector<int> tuitionCosts;
			std::istringstream iss{tuitions};
			std::string c;
			while (getline(iss, c, ',')) { tuitionCosts.emplace_back(std::stoi(c)); }

			info.desc = BlockDesc::AcademicBuilding;
			b = new Academic(name, blockParams[3], purchaseCost, improvLevel, tuitionCosts, improvCost);
		} else if (type == "NonAcademic") {
			int purchaseCost = std::stoi(blockParams[2]);
			int improvLevel = std::stoi(blockParams[3]);
			std::string typeStr = blockParams[4];
			Type t = (typeStr == "Gym") ? Type::Gym : Type::Residence;
			info.desc = BlockDesc::NonAcademicBuilding;
			b = new NonAcademic(name, purchaseCost, improvLevel, t);
		} else if (type == "MoneyBlock") {
			int money = std::stoi(blockParams[2]);
			MoneyType mt = (blockParams[2][0] == '-') ? MoneyType::REMOVE : MoneyType::ADD;
			if (money < 0) money *= -1;
			info.desc = BlockDesc::MoneyBlock;
			b = new MoneyBlock(name, money, mt);
		} else if (type == "MovementBlock") {
			int move = std::stoi(blockParams[2]);
			std::string moveType = blockParams[3];
			MoveType mt = MoveType::MOVE_N_STEPS;
			if (moveType == "TO_BLOCK") {
				mt = MoveType::TO_BLOCK;
			}
			info.desc = BlockDesc::MovementBlock;
			b = new MovementBlock(name, move, mt);
		} else if (type == "Card") {
			int numCards = std::stoi(blockParams[2]);

			std::string probStr = blockParams[3];
			std::string actionStr = blockParams[4];
			std::vector<int> probablities;
			std::vector<std::vector<std::string>> actionList;

			// init the fields above
			std::istringstream sProbStr{probStr};
			std::istringstream sActionStr{actionStr};
			std::string value;
			// init probabilities
			while (getline(sProbStr, value, ',')) { probablities.emplace_back(std::stoi(value)); }
			// init actions
			while (getline(sActionStr, value, ';')) {
				std::istringstream pair{value};
				std::vector<std::string> elem;
				while (getline(pair, value, ',')) { elem.emplace_back(value); }
				actionList.emplace_back(elem);
			}
			
			// create vector of cards
			std::vector<Card> cards;
			for (int i = 0; i < numCards; i++) {
				std::string cmd = actionList[i][0];
				int n = std::stoi(actionList[i][1]);
				double chance = probablities[i];

				Card c;

				if (cmd == "Move") {
					c.action = [n](Player &player) {
						player.move(n);
					};
				} else if (cmd == "MoveTo") {
					c.action = [n](Player &player) {
						player.moveTo(n);
					};
				} else if (cmd == "Remove") {
					c.action = [n](Player &player) {
						player.removeMoney(n);
					};
				} else if (cmd == "Add") {
					c.action = [n](Player &player) {
						player.addMoney(n);
					};
				}
				c.chance = 1.0 / chance;
				cards.emplace_back(c);
			}
			b = new CardBlock(name, numCards, cards);
		} else if (type == "NonProperty") {
			info.desc = BlockDesc::Other;
			b = new MovementBlock(name, 0, MoveType::MOVE_N_STEPS);
		} else {
			// doesn't matter
		}

		b->setInfo(info);
		//b->notifyObservers();
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