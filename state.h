#ifndef STATE_H
#define STATE_H

#include <vector>

class Player;

enum class BlockStateType {
  NewVisitor,
  VisitorLeft,
  Improve,
  Worsen,
  Stable
};
enum class BlockDesc {
  AcademicBuilding,
  NonAcademicBuilding,
  MovementBlock,
  MoneyBlock,
  Other
};

struct BlockState {
  BlockStateType type = BlockStateType::Stable;
  BlockDesc desc = BlockDesc::Other;
  std::vector<Player *> visitors = {};
};

#endif