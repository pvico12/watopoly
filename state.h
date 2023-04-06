#ifndef STATE_H
#define STATE_H

class Player;

enum class PlayerStateType { Stable, Moved, /* add more */ };
enum class BlockStateType { NewVisitor, VisitorLeft, Other };
enum class BlockDesc { AcademicBuilding, NonAcademicBuilding, ChanceMove, ChancePay, Other };

struct PlayerState {
  PlayerStateType type;
  int newPosition;
};

struct BlockState {
  BlockStateType type;
  Player *p = nullptr;
  BlockDesc desc;
};

#endif