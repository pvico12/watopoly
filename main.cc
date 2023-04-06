#include <cstdlib>  // temporary randomness, will add shuffle.cc later
#include <ctime>    // temporary randomness for now, will add shuffle.cc later
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
#include "info.h"
#include "observer.h"
#include "player.h"
#include "state.h"
#include "subject.h"
#include "textdisplay.h"

using namespace std;

int main(int argc, char *argv[]) {
  TextDisplay td;      // initialize a board with constant size
  Board watopoly{td};  // create board (uses .txt file for blocks)

  vector<Player *> players{};
  Player *p;
  p = new Player{"Goose", 'G', Token::GOOSE};
  players.emplace_back(p);
  p = new Player{"GRT Bus", 'B', Token::GRT_BUS};
  players.emplace_back(p);
  p = new Player{"Tim Hortons Doughnut", 'D', Token::DOUGHNUT};
  players.emplace_back(p);
  /* use if needed
  p = new Player{"Professor", 'P', Token::PROFESSOR};
  p = new Player{"Student", 'S', Token::STUDENT};
  p = new Player{"Money", '$', Token::MONEY};
  p = new Player{"Laptop", 'L', Token::LAPTOP};
  p = new Player{"Pink Tie", 'T', Token::PINK_TIE};
  */

  int numPlayers = players.size();
  bool rolled = false;

  vector<Block *> *bs = watopoly.getBlocks();
  vector<Block *> &blocks = *bs;

  // Starting state (game begins at Goose Nesting)
  BlockState s = blocks[0]->getState();
  for (Player *player : players) {
    s.p = player;
    blocks[0]->setState(s);
    blocks[0]->notifyObservers();
  }

  cout << watopoly;  // output text display with starting players

  while (true) {
    int i = 0;
    while (i < numPlayers) {
      Player &player1 = *(players[i]);

      string cmd;
      cin >> cmd;

      char playerChar = player1.getCharToken();
      int pos = player1.getPosition();

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
        BlockState s{BlockStateType::VisitorLeft, BlockDesc::Other, &player1};
        blocks[pos]->setState(s);
        blocks[pos]->notifyObservers();

        player1.move(steps);  // move

        s.type = BlockStateType::NewVisitor;

        // update block state that player is moving to
        blocks[pos + steps]->setState(s);
        blocks[pos + steps]->notifyObservers();

        // update player info
        player1.setPosition(pos + steps);

        // ********* new *********
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
        vector<Academic> academicBuildings = player1.getAcademicProps();
        vector<NonAcademic> nonAcademicBuildings = player1.getNonAcademicProps();
        for (Academic &property : academicBuildings) {
          string propertyName = property.getName();
          cout << propertyName << endl;
        }
        for (NonAcademic &property : nonAcademicBuildings) {
          string propertyName = property.getName();
          cout << propertyName << endl;
        }

      } else if (cmd == "all") {
        for (Player *player : players) {
          cout << player->getName() << endl;
          vector<Academic> academicBuildings = player->getAcademicProps();
          vector<NonAcademic> nonAcacemicBuildings = player->getNonAcademicProps();
          for (Academic &property : academicBuildings) {
            string propertyName = property.getName();
            cout << propertyName << endl;
          }
          for (NonAcademic &property : nonAcacemicBuildings) {
            string propertyName = property.getName();
            cout << propertyName << endl;
          }
          cout << endl;
        }

      } else if (cmd == "save") {
      } else {
        // undefined command
        continue;
      }

      // check if the currrent player is bankrupt

      // check if game is won
    }
  }
}