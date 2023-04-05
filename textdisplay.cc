#include "textdisplay.h"
#include "block.h"

const int NUMSQUARES = 40;
const int BLOCKWIDTH = 8;
const int BLOCKHEIGHT = 5;
const int NUMTOPBLOCKS = 11;
const int NUMBOTBLOCKS = 11;
const int NUMLEFTBLOCKS = 9;
const int NUMRIGHTBLOCKS = 9;
const int MAXWIDTH = 89;
const int MAXHEIGHT = 56;

TextDisplay::TextDisplay() {
	// create empty board
	std::vector<char> emptyRowChars;
	for (int i = 0; i < MAXWIDTH; i++) {
		emptyRowChars.emplace_back(' ');
		}
	for (int i = 0; i < MAXHEIGHT; i++) {
		theDisplay.emplace_back(emptyRowChars);
	}

	// create block coordinate list of top right coordinate of block
	std::vector<int> tmpCoord = {0, 0};
	for (int i = 0; i < NUMTOPBLOCKS; i++) { // top row
		tmpCoord[0] = 0;
		tmpCoord[1] = i*BLOCKWIDTH;
		blockCoords.emplace_back(tmpCoord); 
	}
	for (int i = 1; i < NUMRIGHTBLOCKS+1; i++) { // right column
		tmpCoord[0] = i*BLOCKHEIGHT;
		tmpCoord[1] = MAXWIDTH-BLOCKWIDTH-1;
		blockCoords.emplace_back(tmpCoord);
	}
	for (int i = NUMBOTBLOCKS-1; i >= 0; i--) { // bottom row
		tmpCoord[0] = MAXHEIGHT-BLOCKHEIGHT-1;
		tmpCoord[1] = i*BLOCKWIDTH;
		blockCoords.emplace_back(tmpCoord); 
	}
	for (int i = NUMRIGHTBLOCKS; i > 0; i--) { // right column
		tmpCoord[0] = i*BLOCKHEIGHT;
		tmpCoord[1] = 0;
		blockCoords.emplace_back(tmpCoord);
	}
	
	// draw board
	for (auto coord : blockCoords) {
		int row = coord[0];
		int col = coord[1];
		// draw sides
		for (int i = 1; i <= BLOCKHEIGHT; i++) {
			theDisplay[row+i][col] = '|';
			theDisplay[row+i][col+BLOCKWIDTH] = '|';
		}
		// draw floor
		for (int i = 1; i < BLOCKWIDTH; i++) {
			theDisplay[row+BLOCKHEIGHT][col+i] = '_';
		}
		// draw roof
		if (row == 0) { // top row roof must have all '_'
			for (int i = 0; i < BLOCKWIDTH; i++) {
				theDisplay[row][col+i] = '_';
			}
		} else if (row == MAXHEIGHT-BLOCKHEIGHT-1 && col > 0 && col < MAXWIDTH-2*BLOCKWIDTH-1) {
			// bottom row roof between columns
			for (int i = 1; i <= BLOCKWIDTH; i++) {
				theDisplay[row][col+i] = '_';
			}
		} else { // remaining ones avoid those corners
			for (int i = 1; i < BLOCKWIDTH; i++) {
				theDisplay[row][col+i] = '_';
			}
		}
		theDisplay[0][MAXWIDTH-1] = '_'; // get missing top right corner '_'
	}

	// add WaterPoly Logo !!!
}

void TextDisplay::initDisplay(std::vector<Block*> &blocks) {
	int i = 0;
	for (auto b : blocks) { // loop through blocks
		int row = blockCoords[i][0];    // get its display coordinate
		int col = blockCoords[i][1];
		int rowIter = 1;
		std::string *dispName = b->getDisplayName();      // get its display name
		// iterate through respective coordinates, changing the blocks display
		for (int lineInd = 0; lineInd < BLOCKHEIGHT-1; lineInd++) { 
			std::string line = dispName[lineInd];
			int colIter = 1;
			for (auto c : line) {
				theDisplay[row+rowIter][col+colIter] = c;
				colIter++;
			}
			rowIter++;
		}
		i++;
	}
}

void TextDisplay::notify(Subject<Info, State> &whoNotified) {
	// a block changed state,
	// update the text display of the block
	// perhaps a player visited
	// perhaps an improvement was made on the piece
	Info i = whoNotified.getInfo();
	//State s = whoNotified.getState();
	int pos = i.position;
	int row = blockCoords[pos][0];
	int col = blockCoords[pos][1];
	theDisplay[row+4][col+3] = 'X';
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
	for (auto s : td.theDisplay) {
		for (auto c : s) {
			out << c;
		}
		out << std::endl;
	}
	return out;
}
