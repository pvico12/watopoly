#ifndef STATE_H
#define STATE_H

class Player;

enum class BlockStateType {
  NewVisitor,
  VisitorLeft,
  Other
};
enum class BlockDesc {
  AcademicBuilding,
  NonAcademicBuilding,
  ChanceMove,
  ChancePay,
  Other
};

struct BlockState {
  BlockStateType type;
  BlockDesc desc;
  Player *p;

  BlockState();
  BlockState(BlockStateType type, BlockDesc desc);
  BlockState(BlockStateType type, BlockDesc desc, Player *p);

  BlockState(const BlockState &o);
};

#endif