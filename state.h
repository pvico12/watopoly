#ifndef STATE_H
#define STATE_H

class Player;

enum class BlockStateType { NewVisitor, VisitorLeft, Other };
enum class BlockDesc { AcademicBuilding, NonAcademicBuilding, ChanceMove, ChancePay, Other };

struct BlockState {
  BlockStateType type;
  Player *p = nullptr;
  BlockDesc desc;
};

#endif