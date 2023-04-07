#include <cstdlib>  // temporary randomness, will add shuffle.cc later
#include <ctime>    // temporary randomness for now, will add shuffle.cc later
#include <functional>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

#include "NonProperty/money.h"
#include "NonProperty/movement.h"
#include "NonProperty/nonproperty.h"
#include "Property/academic.h"
#include "Property/nonacademic.h"
#include "Property/property.h"
#include "block.h"
#include "board.h"
#include "info.h"
#include "observer.h"
#include "player.h"
#include "state.h"
#include "subject.h"
#include "textdisplay.h"

using namespace std;

const int MORTGAGE_RATE = 0.5;
const int UNMORTGAGE_RATE = 0.6;

bool isPosInt(const string str) {
  if (str[0] == '0') {
    return false;
  }
  for (char c : str) {
    if (!isdigit(c)) {
      return false;
    }
  }
  return true;
}

void modifyProperty(Player &player, const string cmd, function<void(Property *)> lambda) {
  string propertyName;
  cin >> propertyName;
  Property *property = player.getProperty(propertyName);

  if (property == nullptr) {
    return;
  }

  lambda(property);
}

void printProperties(Player *player) {
  vector<Property *> properties = player->getProperties();

  for (Property *property : properties) {
    string propertyName = property->getName();
    cout << propertyName << endl;
  }
}

void startGame(int &numPlayers, vector<Player *> &players, vector<Block *> &blocks) {
  vector<string> names = {"Goose","GRT Bus","Tim Hortons Doughnut","Professor","Student","Money","Laptop","Pink Tie"};
  vector<char> tokens = {'G','B','D','P','S','$','L','T'};
  
  // determine number of players
  cout << "Enter number of players (2-8): ";
  cin >> numPlayers; // add some precautions if user input is invalid
  cout << endl;

  // print out player name options
  cout << "Here are the avaiable player options:" << endl << endl;
  cout << left << setw(30) << "Names" << "Token" << endl << endl;;
  for (int i = 0; i < 8; i++) {
    cout << left << setw(30) << names[i] << tokens[i] << endl;
  }
  cout << endl;

  // let players choose their desired roles
  for (int i = 1; i <= numPlayers; i++) {
    cout << "Player " << i << " enter player token: ";
    std::string chosenToken;
    std::string chosenName;
    cin >> chosenToken; // add some precautions here too
    cout << endl;

    // find token corresponding to this name
    int ind = 0;
    for (auto token : tokens) {
      if (token == chosenToken[0]) {
        chosenName = names[ind];
        break;
      }
      ind++;
    }

    // create player object and add to its list
    Player *p;
    p = new Player(chosenName, chosenToken[0], Token::GOOSE); // change this Token::GOOSE thing
    players.emplace_back(p);
  }

}

int main(int argc, char *argv[]) {
  TextDisplay td;      // initialize a board with constant size
  Board watopoly{td};  // create board (uses .txt file for blocks)

  vector<Block *> *bs = watopoly.getBlocks();
  vector<Block *> &blocks = *bs;

  // some important values
  int numPlayers;
  bool rolled = false;
  vector<vector<string>> playerTokenList;
  vector<Player *> players;

  startGame(numPlayers, players, blocks);

  // Starting state (game begins at Goose Nesting)
  BlockState s = blocks[0]->getState();
  for (Player *player : players) {
    s.p = player;
    blocks[0]->setState(s);
  }

  cout << watopoly;  // output text display with starting players

  

  while (true) {
    int i = 0;
    while (i < numPlayers) {
      Player &player1 = *(players[i]);
      int pos = player1.getPosition();

      // cmd intake
      string cmd;
      cin >> cmd;

      if (cmd == "roll") {
        if (rolled == true) {
          continue;
        }
        rolled = true;

        srand(time(nullptr));
        int roll1 = (rand() % 6 + 1);
        int roll2 = (rand() % 6 + 1);
        std::cout << "First Dice:  " << roll1 << std::endl;
        std::cout << "Second Dice: " << roll2 << std::endl;
        int steps = roll1 + roll2;

        // set block state
        BlockState s(BlockStateType::VisitorLeft, BlockDesc::Other, &player1);
        blocks[pos]->setState(s);

        player1.move(steps);  // move

        s.type = BlockStateType::NewVisitor;

        // update block state that player is moving to
        blocks[pos + steps]->setState(s);

        // update player info
        player1.setPosition(pos + steps);

        cout << watopoly; 

        // ********* new *********
        /*
        // need getBlock()
        Block block = board.getBlock(player1.getPosition());

        if (dynamic_cast<Property *>(block)) {
          Property *property = dynamic_cast<NonProperty *>(block);
          // case 1: steps on someone else's property
          // case 2: unowned property, purchase
          // case 3: unowned property, auction
        } else if (dynamic_cast<Property *>(block)) {
          NonProperty *nonProperty = dynamic_cast<NonProperty *>(block);
          nonProperty->action();
        } else {
          // should not be here
        }
        */

      } else if (cmd == "next") {
        rolled = false;
        i++;

      } else if (cmd == "trade") {
        /*
        string player2Name;
        cin >> player2Name;
        Player *player2ptr;
        for (int i = 0; i < numPlayers; i++) {
          if (players[1]->getName() == player2Name) {
            player2ptr = players[i];
            break;
          }
        }

        if (player2ptr == nullptr) {
          continue;
        }
        Player &player2 = *player2ptr;

        string str1, str2;
        cin >> str1 >> str2;
        bool b1 = isPosInt(str1);
        bool b2 = isPosInt(str2);

        // check if both are money
        if (b1 && b2) {
          continue;
        }

        if (b1) {
          Property *property2 = player2.getProperty(str1);
          player1.trade(player2, stoi(str1), property2);
        } else if (b2) {
          Property *property1 = player1.getProperty(str1);
          player1.trade(player2, property1, stoi(str2));
        } else {
          Property *property1 = player1.getProperty(str1);
          Property *property2 = player2.getProperty(str1);
          player1.trade(player2, property1, property2);
        }
        */

      } else if (cmd == "improve") {
        modifyProperty(player1, cmd, [&player1](Property *property) {
          Academic *academic = dynamic_cast<Academic *>(property);
          if (academic != nullptr) {
            player1.improve(*academic);
          }
        });

      } else if (cmd == "mortgage") {
        modifyProperty(player1, cmd, [&player1](Property *property) {
          if (player1.hasProperty(*property) && !property->isMortgaged()) {
            player1.addMoney(property->getPurCost() * MORTGAGE_RATE);
            property->toggleMortgage();
            std::cout << "Mortgaged property " << property->getName() << " successfully." << std::endl;
          }
        });

      } else if (cmd == "unmortgage") {
        modifyProperty(player1, cmd, [&player1](Property *property) {
          if (player1.hasProperty(*property) && property->isMortgaged()) {
            bool success = player1.removeMoney(property->getPurCost() * UNMORTGAGE_RATE);
            if (success) {
              property->toggleMortgage();
              std::cout << "Unmortgaged property " << property->getName() << " successfully." << std::endl;
            } else {
              std::cout << "Unmortgaged property " << property->getName() << " failed." << std::endl;
            }
          }
        });

      } else if (cmd == "bankrupt") {
        // reset the owners of the properties that player owns
        // remove any improvements
        // unmortgage any properties in mortgage state
        // remove player from players vector

      } else if (cmd == "assets") {
        printProperties(&player1);

      } else if (cmd == "all") {
        for (Player *player : players) {
          cout << player->getName() << endl;
          printProperties(player);
          cout << endl;
        }

      } else if (cmd == "save") {
      } else {
        // undefined command
        continue;
      }

      // check if the current player is bankrupt
      bool bankrupt = false;  // false for now, change later
      if (bankrupt) {
        // pop player from players vector
        players.erase(players.begin() + i);
      }

      // check if game is won
      if (players.size() == 1) {
        cout << players.at(0)->getName() << " is the winner!" << endl;
      }
    }
  }
}