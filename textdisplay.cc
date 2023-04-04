#include "textdisplay.h"
#include "block.h"

TextDisplay::TextDisplay(std::vector<Block> blocks): numSquares{40} {
	/*
		This was implemented to easily increase board size,
		where the board size must be a multiple of 4.
		Initialize empty board:
		-> Top row is (numSquares/4 + 1) blocks long
		-> The following (numSquares/4 - 1) rows have a block
			 on each end of the row, with selected rows having the
			 WATOPOLY logo in the middle
		-> Bottom row is (numSquares/4 + 1) blocks long
		Note the dimensions of a block
		8 characters wide, 5 characters tall
		Non-Academic Buildings:      Academic Buildings:
		|NAME1                       |
		|NAMECTD                     |-------
		|                    OR      |NAME
		|                            |
		|_______                     |_______
	*/

	int blockWidth = 8;
	int blockHeight = 5;
	int rowBlocks = numSquares/4 + 1;
	int colBlocks = numSquares/4 - 1;
	int maxWidth = rowBlocks*(blockWidth) + 1;
	int maxHeight = (colBlocks+2)*(blockHeight) + 1;

	// Initialize empty board character vector with whitespace chars
	std::vector<char> emptyRowChars;
	for (int i = 0; i < maxWidth; i++) { emptyRowChars.emplace_back(' '); }
	for (int i = 0; i < maxHeight; i++) { theDisplay.emplace_back(emptyRowChars); }

	// Set Up Empty Grid
	for (int i = 0; i < maxWidth; i++) {
		theDisplay[0][i] = '_';
		for (int j = 1; j < maxHeight; j++) {
			bool isLeftCol = (i <= blockWidth);
			bool isRightCol = (i < maxWidth && i >= maxWidth-blockWidth-1);
			bool isFirstRow = (j <= blockHeight);
			bool isLastRow = (j < maxHeight && j >= maxHeight-blockHeight-1);
			if (isLeftCol || isRightCol || isFirstRow || isLastRow) {
				if (i % blockWidth == 0) {
					theDisplay[j][i] = '|';
				} 
				if (i % blockWidth != 0 && j % blockHeight == 0) {
					theDisplay[j][i] = '_';
				}
			}
			if (j == maxHeight-blockHeight-1 && !isLeftCol && !isRightCol) theDisplay[j][i] = '_';
		}
	}

	// Watopoly Logo
	// add watopoly logo code here !!!!!!

	// Top row of blocks
	for (int i = 0; i < rowBlocks; i++) {
		std::string *dispName = blocks[i].getDisplayName();
		for (int j = 1; j < 8; j++) {
			theDisplay[1][i*8+j] = dispName[0][j-1];
			theDisplay[2][i*8+j] = dispName[1][j-1];
			theDisplay[3][i*8+j] = dispName[2][j-1];
			theDisplay[4][i*8+j] = dispName[3][j-1];
		}
	}
	
	// Right column of blocks
	for (int i = 11; i < 11 + 9; i++) {
		std::string *dispName = blocks[i].getDisplayName();
		int col = maxWidth-blockWidth;
		int row = (i-10)*blockHeight+1;
		for (int j = 1; j < 8; j++) {
			theDisplay[row][col] = dispName[0][j-1];
			theDisplay[row+1][col] = dispName[1][j-1];
			theDisplay[row+2][col] = dispName[2][j-1];
			theDisplay[row+3][col] = dispName[3][j-1];
			col++;
		}
	}
	
	// Bottom row of blocks
	for (int i = 20; i < 20 + 11; i++) {
		std::string *dispName = blocks[i].getDisplayName();
		int row = maxHeight-blockHeight;
		for (int j = 1; j < 8; j++) {
			int col = maxWidth - (i-20+1)*blockWidth - 1;
			theDisplay[row][col+j] = dispName[0][j-1];
			theDisplay[row+1][col+j] = dispName[1][j-1];
			theDisplay[row+2][col+j] = dispName[2][j-1];
			theDisplay[row+3][col+j] = dispName[3][j-1];
		}
	}

	// Left column of blocks
	for (int i = 30; i < 40; i++) {
		std::string *dispName = blocks[i].getDisplayName();
		int row = (40-i)*blockHeight+1;
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
