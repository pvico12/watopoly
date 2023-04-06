#include "state.h"

BlockState::BlockState(BlockStateType type, BlockDesc desc)
    : type{type}, desc{desc} {}

BlockState::BlockState(BlockStateType type, BlockDesc desc, Player *p)
    : type{type}, desc{desc}, p{p} {}