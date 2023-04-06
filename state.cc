#include "state.h"

BlockState::BlockState()
    : type{BlockStateType::Other}, desc{BlockDesc::Other}, p{nullptr} {}

BlockState::BlockState(BlockStateType type, BlockDesc desc)
    : type{type}, desc{desc}, p{nullptr} {}

BlockState::BlockState(BlockStateType type, BlockDesc desc, Player *p)
    : type{type}, desc{desc}, p{p} {}

BlockState::BlockState(const BlockState &o)
    : type{o.type}, desc{o.desc}, p{o.p} {}