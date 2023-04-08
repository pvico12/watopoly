#include <iostream>
#include <fstream>

#include "commandInterpreter.h"

using namespace std;

int main(int argc, char *argv[]) {

    if (argc == 1) { // client wants to start a game
        // initialize the board
        // collect information to start the game
        // start to interpret commands

        WatopolyGame yourGame;
        yourGame.play();

    } else if (argc == 2) { // client wants to enter testing mode

        string option = argv[1];

        if (option == "-load") {
            cerr << "Invalid argument. You must add a filename to the command to load in a file." << endl;
            cerr << "You can use the optional command line arguments ./Watopoly -load <filename>" << endl;
        } else if (option == "-testing") {
            // do some stuff, i still don't understand what this does
        } else {
            cerr << "Invalid argument. Optional arguments include only: " << endl;
            cerr << "1. -load <filename>" << endl;
            cerr << "2. -testing" << endl;
        }

    } else if (argc == 3) {  // client wants to load a game

        string option = argv[1];

        if (option == "-load") {
            // check if file(argv[3]) is correct format
            string filename = argv[2];
            ifstream inputFile{filename};
            if (!inputFile.is_open()) {
                cerr << "Unable to open file" << endl;
            } else {
                inputFile.close();
                WatopolyGame loadedGame{filename};
                cout << "The saved state file has been succesfully loaded." << endl;
                loadedGame.play();
            }

        } else {
            cerr << "Invalid argument. Optional arguments include only: " << endl;
            cerr << "1. -load <filename>" << endl;
            cerr << "2. -testing" << endl;
        }

    } else {
        cerr << "Invalid number of arguments." << endl;
    }
}