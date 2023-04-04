#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include <iostream>
#include <vector>

#include "observer.h"
class Block;

class TextDisplay: public Observer {
	std::vector<std::vector<char>> theDisplay;
	const int numSquares;
 public:
	TextDisplay(std::vector<Block> blocks); // intialize empty board

	void notify(Subject &whoNotified) override; // block notifies change of state

	friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
