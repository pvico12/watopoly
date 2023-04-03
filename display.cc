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
	

	// Top row of blocks
	theDisplay[0][0] = '_';
	for (int i = 0; i < numRowBlocks; i++) {
		Block currBlock = blocks[i];
		std::string name = currBloc
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
