#include "board.h"
#include "block.h"
#include "textdisplay.h"
#include "player.h"

#include <string>
#include <vector>
#include <functional>

extern const int MORTGAGE_RATE;
extern const int UNMORTGAGE_RATE;
extern const int STARTING_BLOCK;
extern const std::string separator;

bool isPosInt(const std::string str);

void modifyProperty(Player &player, const std::string cmd, std::function<void(Property *)> lambda);

Player *findPlayer2(std::vector<Player *> &players, std::string player2Name);

void auction(Property *prop, std::vector<Player *> &players);

void printProperties(Player *player);

void printFileToScreen(std::string filename);

void getPlayerData(int &numPlayers, std::vector<Player *> &players);

struct WatopolyGame {
    TextDisplay td;
    Board board;
    bool rolled = false;
    int numPlayers = 0;
    std::vector<Block *> blocks;
    std::vector<Player *> players;

    // construct and initialize
    WatopolyGame(int &playerCount, std::vector<Player *> &players);
    WatopolyGame(std::string filename);

    // game commands
    void roll(Player &p, int &pos, bool &rolled);
    void next(int &playerInd);
    void trade(Player &p1, Player &p2);
    void improve(Player &p, std::string cmd, int pos);
    void mortage(Player &p, std::string cmd);
    void unmortage(Player &p, std::string cmd);
    void bankrupt(Player &p, int &playerInd);
    void assets(Player &p);
    void allAssets();
    void help();
    void save();
    void play();
};