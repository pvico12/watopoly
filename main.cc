#include <iostream>
#include <vector>

#include "NonProperty/money.h"
#include "NonProperty/movement.h"
#include "NonProperty/nonproperty.h"
#include "Property/academic.h"
#include "Property/nonacademic.h"
#include "Property/property.h"
#include "block.h"
#include "board.h"
#include "observer.h"
#include "player.h"
#include "subject.h"
#include "textdisplay.h"
using namespace std;

const int MORTGAGE_RATE = 0.5;
const int UNMORTGAGE_RATE = 0.6;

int main(int argc, char *argv[]) {
  TextDisplay td;      // initialize a board with constant size
  Board watopoly{td};  // create board (uses .txt file for blocks)
  cout << td;          // output text display

  vector<Player> players{};
  int numPlayers = players.size();
  bool rolled = false;

  while (true) {
    int i = 0;
    while (i < players.size()) {
      Player &player1 = players.at(i);

      string cmd;
      cin >> cmd;

      if (cmd == "roll") {
        if (rolled == true) {
          continue;
        }
        
        int steps;  // roll the dice
        player1.move(steps);
        rolled = true;

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

      } else if (cmd == "next") {
        rolled = false;
        i++;

      } else if (cmd == "trade") {
        string player2Name;
        // find player
        Player &player2 = players.at(i);
        string str1;
        string str2;
        cin >> str1;
        cin >> str2;
        // find property1 & property2
        // player1.trade(player2, str1, str2);

      } else if (cmd == "improve") {
        Property &property;
        // intake property
        if (player1.hasProperty(property)) {
          player1.improve(property);
        }

      } else if (cmd == "mortgage") {
        Property &property;
        // intake property
        if (player1.hasProperty(property) && !property.isMortgaged()) {
          property.toggleMortgage();
          player1.addMoney(property.getPurCost() * MORTGAGE_RATE);
        }

      } else if (cmd == "unmortgage") {
        Property &property;
        // intake property
        if (player1.hasProperty(property) && property.isMortgaged()) {
          property.toggleMortgage();
          player1.removeMoney(property.getPurCost() * UNMORTGAGE_RATE);
        }

      } else if (cmd == "bankrupt") {
        // reset the owners of the properties that player owns
        // remove any improvements
        // unmortgage any properties in mortgage state
        // remove player from players vector

      } else if (cmd == "assets") {
        for (Property &property : player1.getProperties()) {
          cout << property << endl;
        }

      } else if (cmd == "all") {
        for (Player &player : players) {
          cout << player.getName() << endl;
          for (Property &property : player.getProperties()) {
            cout << property << endl;
          }
          cout << endl;
        }

      } else if (cmd == "save") {
        // to be implemented
      } else {
        // undefined command
        continue;
      }

      // check if the currrent player is bankrupt

      // check if game is won
    }
  }
}