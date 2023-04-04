#ifndef MOVEMENTBLOCK_H
#define MOVEMENTBLOCK_H

#include "nonproperty.h"
#include "player.h"

enum MoveType {
  MOVE_N_STEPS,
  TO_BLOCK
};

class MovementBlock : public NonProperty {
  int steps;
  MoveType mt;

 public:
  MovementBlock(std::string name, int steps, MoveType mt = MOVE_N_STEPS);
  virtual void action(Player &player);
};

#endif