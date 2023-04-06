#include "info.h"

BlockInfo::BlockInfo()
    : name{""}, position{0}, desc{BlockDesc::Other} {}

BlockInfo::BlockInfo(std::string name, int position)
    : name{name}, position{position} {}

BlockInfo::BlockInfo(std::string name, int position, BlockDesc desc)
    : name{name}, position{position}, desc{desc} {}

BlockInfo::BlockInfo(const BlockInfo &o)
    : name{o.name}, position{o.position}, desc{o.desc} {}