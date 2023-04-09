#include "board.h"
#include "block.h"
#include "textdisplay.h"
#include "player.h"

#include <string>
#include <vector>
#include <functional>

extern const double MORTGAGE_RATE;
extern const double UNMORTGAGE_RATE;
extern const int MAX_CUP_COUNT;
extern const int GET_OUT_OF_TIMS_FEE;
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
    bool rolled;
    bool testing;
    int numPlayers;
    std::vector<Block *> blocks;
    std::vector<Player *> players;

    // construct and initialize
    WatopolyGame(bool testing);
    WatopolyGame(std::string filename, bool testing);

    // game commands
    void roll(Player &p, int &pos, bool &rolled);
    void next(int &playerInd);
    void trade(Player &p1, Player &p2);
    void improve(Player &p, std::string choice, int pos);
    void mortgage(Player &p, std::string cmd);
    void unmortgage(Player &p, std::string cmd);
    void bankrupt(Player &p, int &playerInd);
    void assets(Player &p);
    void allAssets();
    void help();
    void save();
    void play();
};