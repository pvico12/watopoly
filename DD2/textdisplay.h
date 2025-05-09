#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include <iostream>
#include <vector>

#include "observer.h"
#include "info.h"
#include "state.h"

class Block;

extern const int NUMSQUARES;
extern const int BLOCKWIDTH;
extern const int BLOCKHEIGHT;
extern const int NUMTOPBLOCKS;
extern const int NUMBOTBLOCKS;
extern const int NUMLEFTBLOCKS;
extern const int NUMRIGHTBLOCKS;
extern const int MAXWIDTH;
extern const int MAXHEIGHT;
extern const int LOGOROW;
extern const int LOGOCOL;

class TextDisplay: public Observer<BlockInfo, BlockState> {
	std::vector<std::vector<char>> theDisplay;
	std::vector<std::vector<int>> blockCoords;
 public:
	TextDisplay(); // intialize empty board
	
	void initDisplay(std::vector<Block*> &blocks); // fill in board

	// block notifies change of state
	void notify(Subject<BlockInfo, BlockState> &whoNotified) override;
	
	friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
