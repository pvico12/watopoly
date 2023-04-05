#include "state.h"
#include "info.h"
#include "observer.h"
#include "subject.h"
#include "block.h"
#include "board.h"
#include "textdisplay.h"
#include "Property/property.h"
#include "Property/academic.h"
#include "Property/nonacademic.h"

#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {

	TextDisplay td; // initialize a board with constant size
	Board watopoly{td}; // create board (uses .txt file for blocks)
	cout << td; // output text display

	vector<Block*> *blocks = watopoly.getBlocks();
	vector<Block*> &bs = *blocks;
	bs[1]->notifyObservers();

	cout << td;
}
