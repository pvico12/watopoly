#ifndef PLAYER_H
#define PLAYER_H

// forward declaration of property
class Property;

class Player {
  int money;

 public:
  void move(int n); // may put it in board instead of here

  bool buy(Property &prop);

  bool improve(Property &prop);

  bool trade(Player &p); // may need to add additional parameters
};

#endif