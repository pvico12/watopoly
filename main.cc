#include <iostream>
#include <fstream>

#include "commandInterpreter.h"

using namespace std;

bool correctFile(string filename) {
    ifstream inputFile{filename};
    if (!inputFile.is_open()) {
        cerr << "Unable to open file " << filename << "." << endl;
        return false;
    } else {
        inputFile.close();
        return true;
    }
}

int main(int argc, char *argv[]) {

    bool loading = false;
    bool testing = false;
    string filename;
    string option1 = "";
    string option2 = "";
    string option3 = "";
    if (argc == 2)  {
        option1 = argv[1];
    } else if (argc == 3) {
        option2 = argv[2];
    } else if (argc == 4) {
        option3 = argv[3];
    }

    if (argc == 2 && option1 == "-testing") {
        cout << "HERE";
        testing = true;
    } else if (argc == 3 && option1 == "-load") {
        if (correctFile(option2)) {
            loading = true;
            filename = option2;
        }
    } else if (argc == 4) {
        if (option1 == "-testing") testing = true;
        if (option1 == "-load") {
            if (correctFile(option2)) {
                loading = true;
                filename = option2;
            }
        }
        if (option3 == "-testing") testing = true;
    }

    if (loading) {
        WatopolyGame loadedGame{filename, testing};
        cout << "The saved state file has been succesfully loaded." << endl;
        loadedGame.play();
    } else {
        WatopolyGame yourGame{testing};
        yourGame.play();
    }
}