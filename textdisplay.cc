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
	std::vector<char> emptyRowChars;
	for (int i = 0; i < MAXWIDTH; i++) {
		emptyRowChars.emplace_back(' ');
		}
	for (int i = 0; i < MAXHEIGHT; i++) {
		theDisplay.emplace_back(emptyRowChars);
	}

	for (int i = 0; i < MAXWIDTH; i++) {
		theDisplay[0][i] = '_';
		for (int j = 1; j < MAXHEIGHT; j++) {
			bool isLeftCol = (i <= BLOCKWIDTH);
			bool isRightCol = (i < MAXWIDTH && i >= MAXWIDTH-BLOCKWIDTH-1);
			bool isFirstRow = (j <= BLOCKHEIGHT);
			bool isLastRow = (j < MAXHEIGHT && j >= MAXHEIGHT-BLOCKHEIGHT-1);
			if (isLeftCol || isRightCol || isFirstRow || isLastRow) {
				if (i % BLOCKWIDTH == 0) {
					theDisplay[j][i] = '|';
				} 
				if (i % BLOCKWIDTH != 0 && j % BLOCKHEIGHT == 0) {
					theDisplay[j][i] = '_';
				}
			}
			if (j == MAXHEIGHT-BLOCKHEIGHT-1 && !isLeftCol && !isRightCol) theDisplay[j][i] = '_';
		}
	}

	// add WaterPoly Logo
}

void TextDisplay::initDisplay(std::vector<Block> &blocks) {

	// Top row of blocks
	for (int i = 0; i < NUMTOPBLOCKS; i++) {
		std::string *dispName = blocks[i].getDisplayName();
		for (int j = 1; j < 8; j++) {
			theDisplay[1][i*8+j] = dispName[0][j-1];
			theDisplay[2][i*8+j] = dispName[1][j-1];
			theDisplay[3][i*8+j] = dispName[2][j-1];
			theDisplay[4][i*8+j] = dispName[3][j-1];
		}
	}
	
	// Right column of blocks
	for (int i = NUMTOPBLOCKS; i < NUMTOPBLOCKS+NUMRIGHTBLOCKS; i++) {
		std::string *dispName = blocks[i].getDisplayName();
		int col = MAXWIDTH-BLOCKWIDTH;
		int row = (i-10)*BLOCKHEIGHT+1;
		for (int j = 1; j < 8; j++) {
			theDisplay[row][col] = dispName[0][j-1];
			theDisplay[row+1][col] = dispName[1][j-1];
			theDisplay[row+2][col] = dispName[2][j-1];
			theDisplay[row+3][col] = dispName[3][j-1];
			col++;
		}
	}
	
	// Bottom row of blocks
	for (int i = NUMTOPBLOCKS+NUMRIGHTBLOCKS; i < NUMTOPBLOCKS+NUMRIGHTBLOCKS+NUMTOPBLOCKS; i++) {
		std::string *dispName = blocks[i].getDisplayName();
		int row = MAXHEIGHT-BLOCKHEIGHT;
		for (int j = 1; j < 8; j++) {
			int col = MAXWIDTH - (i-20+1)*BLOCKWIDTH - 1;
			theDisplay[row][col+j] = dispName[0][j-1];
			theDisplay[row+1][col+j] = dispName[1][j-1];
			theDisplay[row+2][col+j] = dispName[2][j-1];
			theDisplay[row+3][col+j] = dispName[3][j-1];
		}
	}

	// Left column of blocks
	for (int i = NUMTOPBLOCKS+NUMRIGHTBLOCKS+NUMTOPBLOCKS; i < NUMSQUARES; i++) {
		std::string *dispName = blocks[i].getDisplayName();
		int row = (40-i)*BLOCKHEIGHT+1;
		for (int j = 1; j < 8; j++) {
			theDisplay[row][j] = dispName[0][j-1];
			theDisplay[row+1][j] = dispName[1][j-1];
			theDisplay[row+2][j] = dispName[2][j-1];
			theDisplay[row+3][j] = dispName[3][j-1];
		}
	}
	
}

void TextDisplay::notify(Subject &whoNotified) {
	// a block changed state,
	// update the text display of the block
	// perhaps a player visited
	// perhaps an improvement was made on the piece
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
