#include "state.h"
#include "info.h"
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

#include <iostream>
#include <vector>
#include <cstdlib> // temporary randomness, will add shuffle.cc later
#include <ctime> // temporary randomness for now, will add shuffle.cc later

using namespace std;

int main(int argc, char *argv[]) {
  TextDisplay td;      // initialize a board with constant size
  Board watopoly{td};  // create board (uses .txt file for blocks)

  vector<Player*> players{};
  Player *p;
  p = new Player{"G", Token::GOOSE};
  players.emplace_back(p);
  p = new Player{"B", Token::GRT_BUS};
  players.emplace_back(p);
  p = new Player{"D", Token::DOUGHNUT};
  players.emplace_back(p);
  p = new Player{"B", Token::GRT_BUS};
  p = new Player{"D", Token::DOUGHNUT};
  p = new Player{"P", Token::PROFESSOR};
  p = new Player{"S", Token::STUDENT};
  p = new Player{"$", Token::MONEY};
  p = new Player{"L", Token::LAPTOP};
  p = new Player{"T", Token::PINK_TIE};

  int numPlayers = players.size();
  bool rolled = false;

  vector<Block*> *bs = watopoly.getBlocks();
	vector<Block*> &blocks = *bs;

  for (auto player: players) {
    player->attach(&td);
  }
  
  // Starting state (game begins at Goose Nesting)
  BlockState s = blocks[0]->getState();
  for (Player *player : players) {
    s.p = player;
    blocks[0]->setState(s);
    blocks[0]->notifyObservers();
  }

  cout << watopoly;   // output text display with starting players

  /*
  	vector<Block*> *blocks = watopoly.getBlocks();
	  vector<Block*> &bs = *blocks;
	  bs[1]->notifyObservers();
  */

  while (true) {
    int i = 0;
    while (i < numPlayers) {
      Player &player1 = *(players[i]);

      string cmd;
      cin >> cmd;

      PlayerInfo prevI = player1.getInfo();
      PlayerState prevS = player1.getState();

      if (cmd == "roll") {

		    srand(time(nullptr));
        int roll1 = (rand() % 6 + 1);
        int roll2 = (rand() % 6 + 1);
        std::cout << "First Dice:  " << roll1 << std::endl;
        std::cout << "Second Dice: " << roll2 << std::endl;
        int steps = roll1 + roll2;

        // set block state
        BlockState s;
        s.type = BlockStateType::VisitorLeft;
        s.p = &player1;
        s.desc = BlockDesc::Other;
        blocks[prevI.position]->setState(s);
        blocks[prevI.position]->notifyObservers();

        player1.move(steps); // move

        s.type = BlockStateType::NewVisitor;
        
        // update block state that player is moving to
        blocks[prevI.position + steps]->setState(s);
        blocks[prevI.position + steps]->notifyObservers();

        // update player info
        prevI.position = prevI.position + steps;
        player1.setInfo(prevI);

        rolled = true;

        cout << watopoly;
		
      } else if (cmd == "next") {

        rolled = false;
        i++;

      } else if (cmd == "trade") {

        string player2Name;
        // find player
        //Player &player2 = players.at(i); UNUSED, uncomment when needed
        string str1;
        string str2;
        cin >> str1;
        cin >> str2;
        // find property1 & property2
        // player1.trade(player2, str1, str2);

	  } else if (cmd == "improve") {

        //Property &property;
        //if (player1.hasProperty(property)) {
        //}

      } else if (cmd == "mortgage") {

      } else if (cmd == "unmortgage") {

      } else if (cmd == "bankrupt") {
        // reset the owners of the properties that player owns
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