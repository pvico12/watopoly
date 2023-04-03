#include "textdisplay.h"

TextDisplay::TextDisplay(int n, std::vector<Block>): numSquares{n} {
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

	int blockWidth = 7;
	int blockHeight = 4;
	int numRowBlocks = numSquares/4 + 1;
	int numColBlocks = numSquares/4 - 1;
	int maxWidth = numRowBlocks*(blockWidth+1) + 1;
	int maxHeight = numColBlocks*(blockHeight+1) + 1;

	// Initialize empty board character vector with whitespace chars
	int std::vector<char> emptyRowChars;
	for (int i = 0; i < maxWidth; i++) { emptyRowChars.emplace_back(' ') }
	for (int i = 0: i < maxHeight; i++) { theDisplay.emplace_back(emptyRowChars) }

	// Set Up Empty Grid
	for (int i = 0; i < maxWidth; i++) {
		theDisplay[0][i] = '_';
		
		for (int j = 0; j < maxHeight; j++) {
			
			if (i % (blockWidth+1) == 0) {
				theDisplay[i][j] = '|';
			} else {
				
				if (j % (blockHeight+1) == 0) {
					theDisplay[i][j] = "_";
				}

			}

		}
	}

	// Watopoly Logo
	// add watoply logo code here !!!!!!

	// Top row of blocks
	for (int i = 0; i < numRowBlocks; i++) {
		Block currBlock = blocks[i];
		std::string name = currBlock.getName();
		int startNameIndex = i*(blockWidth+1) + 1;
		int endNameIndex = (i+1)*(blockWidth+1);
		for (int j = startNameIndex; j < endNameIndex; j++) {
			theDisplay[1][j] = name[startNameIndex - j];
		}
	}

	// Right column of blocks
	for (int i = numRowBlocks; i < numRowBlocks + numColBlocks; i++) {
		Block currBlock = blocks[i];
		std::string name = currBlock.getName();
		int startNameIndex = maxWidth-blockWidth-1;
		int endNameIndex = maxWidth-1;
		for (int j = 0; j < numColBlocks; j++) {
			// insert code
		}
	}
	
	// Bottom row of blocks

	// Left column of blocks

}

void TextDisplay::notify(Subject &whoNotified) override {
	// a block changed state,
	// update the text display of the block
}

std::ostream TextDisplay::&operator(std::ostream &out, const TextDisplay &td) {
	int currInd = 1;
	int maxWidth = (numSquares/4 + 1)*8 + 1;
	for (auto c : td.theDisplay) {
		if (currInd > maxWidth) {
			// newline when index reaches width
			out << std::endl;
			currInd = 1;
		}
		out << c;
		currInd++;
	}
	return out;
}
