#include <cstdlib>  // temporary randomness, will add shuffle.cc later
#include <ctime>    // temporary randomness for now, will add shuffle.cc later
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
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
#include "token.h"

using namespace std;

const int MORTGAGE_RATE = 0.5;
const int UNMORTGAGE_RATE = 0.6;
const int STARTING_BLOCK = 20;
const string separator = " ";

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

Player *findPlayer2(vector<Player *> &players, string player2Name) {
  Player *player2ptr;
  int numPlayers = players.size();
  for (int i = 0; i < numPlayers; i++) {
    if (players.at(i)->getName() == player2Name) {
      player2ptr = players.at(i);
      return player2ptr;
    }
  }
  return nullptr;
}

void auction(Property *prop, std::vector<Player *> &players) {
  cout << "Starting auction for " << prop->getName() << "..." << endl;

  int cost = prop->getPurCost();
  int bidders = 0;
  Player *highestBidder = nullptr;
  int highestBid = 0;

  while (true) {
    int previousHigh = highestBid;
    for (Player *player : players) {
      // check if the player has enough money to make a higher bid
      if (player->getMoney() < highestBid) {
        continue;
      }

      cout << "Current highest bid: " << highestBid << endl;
      cout << player->getName() << ", please enter your bid: ";
      int bid;
      cin >> bid;
      cout << endl;

      if (bid > highestBid) {
        highestBidder = player;
        highestBid = bid;
      }
    }

    if (highestBid == previousHigh) {
      break;
    }
  }

  if (highestBidder != nullptr) {
    highestBidder->removeMoney(cost);
    highestBidder->addProperty(*prop);
    cout << prop->getName() << " has been auctioned to " << highestBidder->getName() << endl;
  } else {
    cout << "No one bid, " << prop->getName() << " remains unowned." << endl;
  }
}

void printProperties(Player *player) {
  vector<Property *> properties = player->getProperties();

  for (Property *property : properties) {
    string propertyName = property->getName();
    cout << propertyName << endl;
  }
}

void printFileToScreen(std::string filename) {
  ifstream file{filename};
  string line;
  while (getline(file, line)) {
    cout << line << endl;
  }
  file.close();
}

void getPlayerData(int &numPlayers, vector<Player *> &players) {
  // determine number of players
  cout << "Enter number of players (2-8): ";
  cin >> numPlayers;  // add some precautions if user input is invalid
  cout << endl;

  // print out player name options
  cout << "Here are the available player options:" << endl
       << endl;
  cout << left << setw(30) << "Names"
       << "Token" << endl
       << endl;

  for (auto &t : tokenToStrMap) {
    cout << left << setw(30) << t.second;
    Token token = strToTokenMap[t.second];
    cout << left << setw(5) << tokenToCharMap[token] << endl;
  }
  cout << endl;

  // let players choose their desired roles
  for (int i = 1; i <= numPlayers; i++) {
    cout << "Player " << i << " enter name: ";
    std::string playerName;
    cin >> playerName;  // add some precautions here too
    std::string chosenToken;
    cout << "Please enter the token of which piece you would like on the board (e.g. G): ";
    cin >> chosenToken;  // add some precautions here too
    cout << endl;

    // create player object and add to its list
    Player *p;
    p = new Player(playerName, charToTokenMap[chosenToken[0]], 1500, STARTING_BLOCK);  // put players at Collect OSAP block
    players.emplace_back(p);
  }
}

void startGame(int &numPlayers, vector<Player *> &players, vector<Block *> &blocks) {
  printFileToScreen("introMessage.txt");
  getPlayerData(numPlayers, players);

  // Starting state (game begins at Goose Nesting)
  BlockState s = blocks[0]->getState();
  for (Player *player : players) {
    s.p = player;
    blocks[STARTING_BLOCK]->setState(s);
  }

  printFileToScreen("rules.txt");
  printFileToScreen("commands.txt");
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
  cout << watopoly;  // output text display with starting players

  while (true) {
    int i = 0;
    string startingPlayerName = players.at(0)->getName();
    cout << "Control is now given to " << startingPlayerName << endl;
    while (i < numPlayers) {
      Player &player1 = *(players.at(i));
      std::string player1Name = player1.getName();
      int pos = player1.getPosition();

      // cmd intake
      string cmd;
      cin >> cmd;

      if (cmd == "roll") {
        if (rolled) {
          // player has already rolled,
          // output an informative message on what further commands they can use
          cout << "You have attempted to roll more then once." << endl;
          cout << "You may either use the command 'next' to give control to the next player, OR" << endl;
          cout << "You may use other commands to take action on the square landed." << endl;
          cout << "For help with commands or the rules of the game, enter the command 'help'." << endl;
          continue;
        } else {
          // you can now move the player
          rolled = true;

          srand(time(nullptr));
          int roll1 = (rand() % 6 + 1);
          int roll2 = (rand() % 6 + 1);
          std::cout << "First Dice:  " << roll1 << std::endl;
          std::cout << "Second Dice: " << roll2 << std::endl;
          int steps = roll1 + roll2;

          // set original block state to visitor leaving, remove player from this block
          BlockState currPosState = blocks[pos]->getState();
          currPosState.type = BlockStateType::VisitorLeft;
          currPosState.p = &player1;
          blocks[pos]->setState(currPosState);

          player1.move(steps);  // move

          // update block state that player is moving to
          int newPosition = (pos + steps >= NUMSQUARES) ? (pos + steps) % NUMSQUARES : pos + steps;
          BlockState newPosState = blocks[newPosition]->getState();
          newPosState.type = BlockStateType::NewVisitor;
          newPosState.p = &player1;
          blocks[newPosition]->setState(newPosState);

          // update player info
          player1.setPosition(newPosition);

          // ********* new *********
          BlockInfo info = blocks[pos]->getInfo();
          BlockDesc desc = info.desc;
          Player *owner = info.owner;

          if (desc == BlockDesc::AcademicBuilding && desc == BlockDesc::NonAcademicBuilding) {
            Property *property = dynamic_cast<Property *>(blocks[pos]);
            if (owner) {
              // case 1: steps on someone else's property
              int amount = property->getFee();
              Player *player2ptr = findPlayer2(players, owner->getName());
              Player player2 = *player2ptr;
              bool isBankrupt = !player1.hasMoney(amount);
              if (isBankrupt) {
                cout << "Would you like to mortgage or trade with other players to prevent bankruptcy?" << endl;
              }
              player1.removeMoney(amount);
              player2.addMoney(amount);
            } else {
              // check if it's the current player's property
              if (owner == &player1) {
                continue;
              }

              string purchase;
              cout << "Would you like to purchase this unowned property? (Yes/No)";
              cin >> purchase;
              cout << endl;
              int fee = property->getFee();

              if (purchase == "Yes") {
                // case 2: unowned property, purchase
                if (player1.hasMoney(fee)) {
                  player1.removeMoney(fee);
                  player1.addProperty(*property);  // need to check if this works
                  cout << "Purchase successful! You now own " << property->getName() << "." << endl;
                  continue;
                } else {
                  cout << "Purchase failed! You have insufficient funds." << endl;
                }
              }
              // case 3: unowned property, auction
              auction(property, players);
            }
          } else if (desc == BlockDesc::MovementBlock) {
            NonProperty *nonProperty = dynamic_cast<NonProperty *>(blocks[pos]);
            nonProperty->action(player1);
            // add additional lines
          } else if (desc == BlockDesc::MoneyBlock) {
            NonProperty *nonProperty = dynamic_cast<NonProperty *>(blocks[pos]);
            nonProperty->action(player1);
          } else {
            // should not be here
          }
        }
      } else if (cmd == "next") {
        // control is given to the next player
        if (!rolled) {
          cout << "Invalid command. You have not rolled yet." << endl;
          continue;
        }
        rolled = false;
        i++;
        if (i >= numPlayers) {
          i = 0;
        }
        // output an informative message
        string newPlayerName = players.at(i)->getName();
        cout << "Control is now given to " << newPlayerName << endl;
      } else if (cmd == "trade") {
        string player2Name;
        cin >> player2Name;
        Player *player2ptr = findPlayer2(players, player2Name);

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
          player1.trade(player2, stoi(str1), *property2);
        } else if (b2) {
          Property *property1 = player1.getProperty(str1);
          player1.trade(player2, *property1, stoi(str2));
        } else {
          Property *property1 = player1.getProperty(str1);
          Property *property2 = player2.getProperty(str1);
          player1.trade(player2, *property1, *property2);
        }
      } else if (cmd == "improve") {
        BlockInfo info = blocks[pos]->getInfo();
        BlockDesc desc = info.desc;
        Player *owner = info.owner;

        if (desc == BlockDesc::AcademicBuilding) {
          if (owner) {
            // this player has purchase the property
            // implement this to work, we need to call buy function
            // but these are blocks so we cant access them
            // PROBLEM: player1.buy(*(blocks)[pos]);
            info.owner = &player1;
            info.impLevel++;
            blocks[pos]->setInfo(info);
          } else {
            // check if the player already owns the property
            if (owner->getName() == player1Name) {
              // improve the property
              info.impLevel++;
              blocks[pos]->setInfo(info);
            } else {
              // if not, output an informative message
              cerr << "Invalid command. You do not own this property." << endl;
            }
          }
        } else if (desc == BlockDesc::AcademicBuilding) {
        } else {
        }

        modifyProperty(player1, cmd, [&player1](Property *property) {
          Academic *academic = dynamic_cast<Academic *>(property);
          if (academic != nullptr) {
            player1.improve(*academic);
          }
        });
      } else if (cmd == "mortgage") {
        modifyProperty(player1, cmd, [&player1](Property *property) {
          int mortgageFee = property->getPurCost() * MORTGAGE_RATE;
          if (player1.hasProperty(*property) && !property->isMortgaged()) {
            player1.addMoney(mortgageFee);
            property->toggleMortgage();
            std::cout << "Mortgaged property " << property->getName() << " successfully." << std::endl;
          }
        });
      } else if (cmd == "unmortgage") {
        modifyProperty(player1, cmd, [&player1](Property *property) {
          if (player1.hasProperty(*property) && property->isMortgaged()) {
            int unMortgageFee = property->getPurCost() * UNMORTGAGE_RATE;
            bool success = player1.hasMoney(unMortgageFee);
            if (success) {
              player1.removeMoney(unMortgageFee);
              property->toggleMortgage();
              std::cout << "Unmortgaged property " << property->getName() << " successfully." << std::endl;
            } else {
              std::cout << "Unmortgaged property " << property->getName() << " failed." << std::endl;
            }
          }
        });
      } else if (cmd == "bankrupt") {
        // need to reset the owners of the properties that player owns
        // remove from tims cups total
        player1.reset();
        players.erase(players.begin() + i);
        numPlayers--;
      } else if (cmd == "assets") {
        printProperties(&player1);
      } else if (cmd == "all") {
        for (Player *player : players) {
          cout << player->getName() << endl;
          printProperties(player);
          cout << endl;
        }
      } else if (cmd == "help") {
        cout << "Would you like to see the rules or the list of commands or both?\n"
             << "Enter rules/commands/both: ";
        string helpCmd;
        cin >> helpCmd;
        cout << endl;
        if (helpCmd == "rules") {
          printFileToScreen("rules.txt");
        } else if (helpCmd == "commands") {
          printFileToScreen("commands.txt");
        } else if (helpCmd == "both") {
          printFileToScreen("rules.txt");
          printFileToScreen("commands.txt");
        } else {
          cout << "Incorrect input. You have exited the help menu.\n"
               << "If you wish to try again, enter the 'help' command." << endl;
        }
      } else if (cmd == "save") {
        // get file name and create file
        std::string filename;
        cin >> filename;
        ofstream outFile{filename};
        // write player info
        outFile << numPlayers << endl;
        for (auto player : players) {
          outFile << player->getName() << separator;
          outFile << player->getCharToken() << separator;
          outFile << player->getTimsCups() << separator;
          outFile << player->getMoney() << separator;
          outFile << player->getPosition() << endl;
          // add case for when in tims line
        }
        // write block info
        for (auto block : blocks) {
          BlockInfo b = block->getInfo();
          std::string blockName = b.name;
          Player *owner = b.owner;
          int impLevel = b.impLevel;
          std::string ownerName = "BANK";
          if (owner) ownerName = owner->getName();
          if (b.desc == BlockDesc::AcademicBuilding ||
              b.desc == BlockDesc::NonAcademicBuilding) {
            outFile << blockName << separator;
            outFile << ownerName << separator;
            outFile << impLevel << endl;
          }
        }
        outFile.close();
      } else {
        // undefined command
        cout << "Invalid command. Use 'help' to see a list of commands and rules." << endl;
        continue;
      }

      // check if game is won
      if (numPlayers == 1) {
        cout << players.at(0)->getName() << " is the winner!" << endl;
        break;
      }

      cout << watopoly;
    }
  }
}