#include "movement.h"

MovementBlock::MovementBlock(std::string name, int steps, MoveType mt)
    : NonProperty{name}, steps{steps}, mt{mt} {}

void MovementBlock::action(Player &player) {
  if (mt == MOVE_N_STEPS) {
    player.move(steps);
  } else if (mt == TO_BLOCK) {
    player.moveTo(steps);
  }
}