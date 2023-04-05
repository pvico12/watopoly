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
#include <cstdlib> // temporary randomness
#include <ctime> // temporary randomness

using namespace std;

int main(int argc, char *argv[]) {
  TextDisplay td;      // initialize a board with constant size
  Board watopoly{td};  // create board (uses .txt file for blocks)
  cout << watopoly;          // output text display

  vector<Player> players{};
  Player p1{"G", Token::GOOSE};
  Player p2{"B", Token::GRT_BUS};
  Player p3{"D", Token::DOUGHNUT};
  Player p4{"P", Token::PROFESSOR};
  Player p5{"S", Token::STUDENT};
  Player p6{"$", Token::MONEY};
  Player p7{"L", Token::LAPTOP};
  Player p8{"T", Token::PINK_TIE};
  players.emplace_back(p1);
  players.emplace_back(p2);
  players.emplace_back(p3);

  int numPlayers = players.size();
  bool rolled = false;

  /*
  	vector<Block*> *blocks = watopoly.getBlocks();
	vector<Block*> &bs = *blocks;
	bs[1]->notifyObservers();
  */

  while (true) {
    int i = 0;
    while (i < numPlayers) {
      Player &player1 = players[i];

      string cmd;
      cin >> cmd;

      if (cmd == "roll") {

		srand(time(nullptr));
        int steps = rand() % 6 + 1;  // roll the dice
        player1.move(steps);
        rolled = true;
		
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

        for (Player &player : players) {
          cout << player.getName() << endl;
		  vector<Academic> academicBuildings = player.getAcademicProps();
		  vector<NonAcademic> nonAcacemicBuildings = player.getNonAcademicProps();
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
	  cout << watopoly;
    }
  }
}