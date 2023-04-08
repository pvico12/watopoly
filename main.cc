#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "commandInterpreter.h"
#include "block.h"
#include "board.h"
#include "textdisplay.h"
#include "player.h"

using namespace std;

int main(int argc, char *argv[]) {

    // some important variables for a game
    int numPlayers;
    vector<Player *> players;

    TextDisplay td;      // initialize a board with constant size
    Board watopoly{td};  // create board (uses .txt file for blocks)
    vector<Block *> *bs = watopoly.getBlocks();  // create list of blocks
    vector<Block *> &blocks = *bs;               // store a copy by reference

    if (argc == 1) { // client wants to start a game
        // initialize the board
        // collect information to start the game
        // start to interpret commands

        WatopolyGame yourGame{numPlayers, players};
        yourGame.play();

    } else if (argc == 2) { // client wants to enter testing mode
        if (argv[1] == "-load") {
            cerr << "Invalid argument. You must add a filename to the command to load in a file." << endl;
            cerr << "You can use the optional command line arguments ./Watopoly -load <filename>" << endl;
        } else if (argv[1] == "-testing") {
            // do some stuff, i still don't understand what this does
        } else {
            cerr << "Invalid argument. Optional arguments include only: " << endl;
            cerr << "1. -load <filename>" << endl;
            cerr << "2. -testing" << endl;
        }

    } else if (argc == 3) {  // client wants to load a game

        if (argv[2] == "-load") {
            // check if file(argv[3]) is correct format
        } else {
            cerr << "Invalid argument. Optional arguments include only: " << endl;
            cerr << "1. -load <filename>" << endl;
            cerr << "2. -testing" << endl;
        }

    } else {
        cerr << "Invalid number of arguments." << endl;
    }
}