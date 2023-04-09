#include "commandInterpreter.h"

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

const double MORTGAGE_RATE = 0.5;
const double UNMORTGAGE_RATE = 0.6;
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
  cout << "Choose your property: ";
  string propertyName;
  cin >> propertyName;
  cout << endl;
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
  Player *highestBidder = nullptr;
  int highestBid = 0;

  int numPlayers = players.size();
  int numBidders = numPlayers;

  while (true) {
    int previousHigh = highestBid;
    for (Player *player : players) {
      if (numBidders <= 1) {
        break;
      }

      // check if the player has enough money to make a higher bid
      if (player->getMoney() < highestBid) {
        numBidders--;
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
        numBidders = numPlayers;
      } else {
        numBidders--;
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

// game constructors
WatopolyGame::WatopolyGame()
    : rolled{false}, numPlayers{0} {
  Board watopoly{td};  // create board (uses .txt file for blocks)
  board = watopoly;
  blocks = *(board.getBlocks());  // create list of blocks

  printFileToScreen("introMessage.txt");
  getPlayerData(numPlayers, players);

  numPlayers = players.size();

  // Starting state (game begins at Collect OSAP)
  BlockState s = blocks[STARTING_BLOCK]->getState();
  for (Player *player : players) {
    vector<Player *> &visitors = s.visitors;
    visitors.emplace_back(player);
    s.type = BlockStateType::Visitors;
    blocks[STARTING_BLOCK]->setState(s);
  }

  printFileToScreen("rules.txt");
  printFileToScreen("commands.txt");
}

// construct game from file
WatopolyGame::WatopolyGame(string filename)
    : rolled{false}, numPlayers{0} {
  Board watopoly{td};  // create board (uses .txt file for blocks)
  board = watopoly;
  blocks = *(board.getBlocks());  // create list of blocks

  ifstream gameStateFile{filename};
  string line;

  // load game info into board
  int lineNum = 0;
  while (getline(gameStateFile, line)) {
    if (lineNum == 0) {
      // read in num players
      numPlayers = stoi(line);
    } else if (lineNum <= numPlayers) {
      // read in players
      vector<string> playerData;
      istringstream iss{line};
      string data;
      while (getline(iss, data, ' ')) {
        playerData.emplace_back(data);
      }

      string playerName = playerData[0];
      char playerChar = playerData[1][0];
      int timsCups = stoi(playerData[2]);
      int money = stoi(playerData[3]);
      int position = stoi(playerData[4]);

      Player *p;
      p = new Player(playerName, charToTokenMap[playerChar], money, position, {}, timsCups);
      players.emplace_back(p);

      // update the block at player position for display
      BlockState state = blocks[position]->getState();
      state.type = BlockStateType::Visitors;
      vector<Player *> &visitors = state.visitors;
      visitors.emplace_back(p);
      blocks[position]->setState(state);
    } else {
      // read in properties
      vector<string> propertyData;
      istringstream iss{line};
      string data;
      while (getline(iss, data, ' ')) {
        propertyData.emplace_back(data);
      }

      string propName = propertyData[0];
      string owner = propertyData[1];
      int numImp = stoi(propertyData[2]);

      // get block position
      int position = 0;
      for (auto b : blocks) {
        BlockInfo info = b->getInfo();
        if (info.name == propName) {
          position = info.position;
          break;
        }
      }

      // update BlockInfo with owner and improvements
      BlockInfo info = blocks[position]->getInfo();
      for (auto currPlayer : players) {
        if (currPlayer->getName() == owner) {
          info.owner = currPlayer;
          info.impLevel = numImp;
        }
      }
      blocks[position]->setInfo(info);
      // update block state so it shows on the display
      BlockState state = blocks[position]->getState();
      state.type = BlockStateType::Improvements;
      blocks[position]->setState(state);
    }
    lineNum++;
  }

  gameStateFile.close();
}

// game commands
void WatopolyGame::roll(Player &p, int &pos, bool &rolled) {
  // you can now move the player
  rolled = true;

  srand(time(nullptr));
  int roll1 = (rand() % 6 + 1);
  int roll2 = (rand() % 6 + 1);
  std::cout << "First Dice:  " << roll1 << std::endl;
  std::cout << "Second Dice: " << roll2 << std::endl;
  int steps = roll1 + roll2;

  // set original block state, remove player from this block
  BlockState currPosState = blocks[pos]->getState();
  currPosState.type = BlockStateType::Visitors;
  vector<Player *> &visitors = currPosState.visitors;
  int targetIndex = 0;
  for (auto player : visitors) {
    if (player->getName() == p.getName()) break;
    targetIndex++;
  }
  visitors.erase(visitors.begin() + targetIndex);
  blocks[pos]->setState(currPosState);

  p.move(steps);  // move

  // update block state that player is moving to
  int newPosition = (pos + steps >= NUMSQUARES) ? (pos + steps) % NUMSQUARES : pos + steps;
  BlockState newPosState = blocks[newPosition]->getState();
  newPosState.type = BlockStateType::Visitors;
  newPosState.visitors.emplace_back(&p);
  blocks[newPosition]->setState(newPosState);

  // update player info
  p.setPosition(newPosition);

  cout << board;

  // ********* new *********
  BlockInfo info = blocks[newPosition]->getInfo();
  BlockDesc desc = info.desc;
  Player *owner = info.owner;

  while (true) {
    if (desc == BlockDesc::AcademicBuilding || desc == BlockDesc::NonAcademicBuilding) {
      Property *property = dynamic_cast<Property *>(blocks[newPosition]);
      if (owner) {
        // case 1: steps on someone else's property
        int amount = property->getFee();
        Player *player2ptr = findPlayer2(players, owner->getName());
        Player player2 = *player2ptr;
        bool isBankrupt = !p.hasMoney(amount);
        if (isBankrupt) {
          cout << "Would you like to mortgage or trade with other players to prevent bankruptcy?" << endl;
        }
        p.removeMoney(amount);
        player2.addMoney(amount);
      } else {
        // check if it's the current player's property
        if (owner == &p) {
          continue;
        }

        int cost = property->getPurCost();
        string purchase;
        cout << "Would you like to purchase this unowned property for $" << to_string(cost) << " (Yes/No)? ";
        cin >> purchase;
        cout << endl;

        if (purchase == "Yes") {
          // case 2: unowned property, purchase
          if (p.hasMoney(cost)) {
            p.removeMoney(cost);
            p.addProperty(*property);  // need to check if this works
            cout << "Purchase successful! You now own " << property->getName() << "." << endl;
            info.owner = &p;
            blocks[newPosition]->setInfo(info);
            break;
          } else {
            cout << "Purchase failed! You have insufficient funds." << endl;
          }
          break;
        } 
      }
    } else if (desc == BlockDesc::MovementBlock) {
      NonProperty *nonProperty = dynamic_cast<NonProperty *>(blocks[newPosition]);
      nonProperty->action(p);
      break;
    } else if (desc == BlockDesc::MoneyBlock) {
      NonProperty *nonProperty = dynamic_cast<NonProperty *>(blocks[newPosition]);
      nonProperty->action(p);
      break;
      // } else if (desc == BlockDesc::Tims) {

      } else {
      // should not be here
      break;
    }
  }
}

void WatopolyGame::next(int &playerInd) {
  // control is given to the next player
  rolled = false;
  playerInd++;
  if (playerInd >= numPlayers) {
    playerInd = 0;
  }
  // output an informative message
  string newPlayerName = players.at(playerInd)->getName();
  cout << "Control is now given to " << newPlayerName << endl;
}

void WatopolyGame::trade(Player &p1, Player &p2) {
  string str1, str2;
  cin >> str1 >> str2;
  bool b1 = isPosInt(str1);
  bool b2 = isPosInt(str2);

  // check if both are money
  if (b1 && b2) {
    cout << "You cannot trade money for money." << endl;
    return;
  }

  bool success;
  if (b1) {
    Property *property2 = p2.getProperty(str1);
    success = p1.trade(p2, stoi(str1), *property2);
  } else if (b2) {
    Property *property1 = p1.getProperty(str1);
    success = p1.trade(p2, *property1, stoi(str2));
  } else {
    Property *property1 = p1.getProperty(str1);
    Property *property2 = p2.getProperty(str1);
    success = p1.trade(p2, *property1, *property2);
  }

  if (success) {
    cout << "You have successfully traded " << (b1 ? "$" : "") << str1 << " for "
         << p2.getName() << "'s " << (b2 ? "$" : "") << str2 << "." << endl;
  } else {
    cout << "Trade failed." << endl;
  }
}

void WatopolyGame::improve(Player &p, string choice, int pos) {
  BlockInfo info = blocks[pos]->getInfo();
  BlockState state = blocks[pos]->getState();
  BlockDesc desc = info.desc;
  Player *owner = info.owner;

  if (desc == BlockDesc::AcademicBuilding) {
    if (owner) {
      if (owner->getName() == p.getName()) {
        // TO ADD: Check if player has monopoly
        if (choice == "buy") {
          state.type = BlockStateType::Improvements;
          info.impLevel++;
        } else if (choice == "sell") {
          state.type = BlockStateType::Improvements;
          info.impLevel--;
        } else {
          cerr << "Invalid command." << endl;
        }
        blocks[pos]->setInfo(info);
        blocks[pos]->setState(state);
      } else {
        cerr << "Invalid command. You do not own this property." << endl;
      } 
    } else {
      cerr << "Invalid command. You do not own this property." << endl;
    }
  } else {
    cerr << "Invalid command. You can only improve Academic Properties that you own." << endl;
  }
  /*
  modifyProperty(p, cmd, [&p](Property *property) {
      Academic *academic = dynamic_cast<Academic *>(property);
      if (academic != nullptr) {
      p.improve(*academic);
      }
  });
  */
}

void WatopolyGame::mortgage(Player &p, string cmd) {
  modifyProperty(p, cmd, [&p](Property *property) {
    if (p.hasProperty(*property) == -1) {
      cout << "You don't own " << property->getName() << "." << endl;
      return;
    }
    if (property->isMortgaged()) {
      cout << property->getName() << " is mortgaged already." << endl;
      return;
    }
    int mortgageFee = property->getPurCost() * MORTGAGE_RATE;
    p.addMoney(mortgageFee);
    property->toggleMortgage();
    cout << "Mortgaged property " << property->getName() << " successfully." << std::endl;
  });
}

void WatopolyGame::unmortgage(Player &p, string cmd) {
  modifyProperty(p, cmd, [&p](Property *property) {
    if (p.hasProperty(*property) == -1) {
      cout << "You don't own " << property->getName() << "." << endl;
      return;
    }
    if (!property->isMortgaged()) {
      cout << property->getName() << " is not mortgaged." << endl;
      return;
    }
    int unMortgageFee = property->getPurCost() * UNMORTGAGE_RATE;
    bool success = p.hasMoney(unMortgageFee);
    if (success) {
      p.removeMoney(unMortgageFee);
      property->toggleMortgage();
      cout << "Unmortgaged property " << property->getName() << " successfully." << endl;
    } else {
      cout << "Unmortgaged property " << property->getName() << " failed, insufficient funds." << endl;
    }
  });
}

void WatopolyGame::bankrupt(Player &p, int &playerInd) {
  // need to reset the owners of the properties that player owns
  // remove from tims cups total
  p.reset();
  players.erase(players.begin() + playerInd);
  numPlayers--;
}

void WatopolyGame::assets(Player &p) {
  printProperties(&p);
}

void WatopolyGame::allAssets() {
  for (Player *player : players) {
    cout << player->getName() << endl;
    printProperties(player);
    cout << endl;
  }
}

void WatopolyGame::help() {
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
}

void WatopolyGame::save() {
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
}

void WatopolyGame::play() {
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
          roll(player1, pos, rolled);
        }
      } else if (cmd == "next") {
        if (!rolled) {
          cout << "Invalid command. You have not rolled yet." << endl;
          continue;
        }
        next(i);
      } else if (cmd == "trade") {
        string player2Name;
        cin >> player2Name;
        Player *player2ptr = findPlayer2(players, player2Name);

        if (player2ptr == nullptr) {
          continue;
        }
        Player &player2 = *player2ptr;

        trade(player1, player2);

      } else if (cmd == "improve") {
        string propName;
        cin >> propName;
        string choice;
        cin >> choice;
        if (choice != "buy" && choice != "sell") {
          cerr << "Invalid command." << endl;
          continue;
        }
        // see if property even exists
        int propIndex = -1;
        int currInd = 0;
        for (auto b : blocks) {
          if (b->getName() == propName) {
            propIndex = currInd;
          }
          currInd++;
        }
        if (propIndex == -1) { 
          cerr << "Invalid command." << endl;
          continue;
        }

        improve(player1, choice, propIndex);
      } else if (cmd == "mortgage") {
        mortgage(player1, cmd);
      } else if (cmd == "unmortgage") {
        unmortgage(player1, cmd);
      } else if (cmd == "bankrupt") {
        bankrupt(player1, i);
      } else if (cmd == "assets") {
        assets(player1);
      } else if (cmd == "all") {
        allAssets();
      } else if (cmd == "help") {
        help();
      } else if (cmd == "save") {
        save();
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

      cout << board;
      for (Player *player : players) {
        vector<Property *> properties = player->getProperties();
        int money = player->getMoney();
        cout << player->getName() << endl;
        cout << to_string(money) << endl;
        for (auto property : properties) {
          cout << property->getName() << endl;
        }
        cout << endl;
      }
    }
  }
}
