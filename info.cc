#include "info.h"

BlockInfo::BlockInfo(std::string name, int position)
    : name{name}, position{position} {}

BlockInfo::BlockInfo(std::string name, int position, BlockDesc desc)
    : name{name}, position{position}, desc{desc} {}