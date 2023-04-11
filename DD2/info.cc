#include "info.h"

BlockInfo::BlockInfo()
    : name{""}, position{0}, desc{BlockDesc::Other}, owner{nullptr}, impLevel{0} {}

BlockInfo::BlockInfo(std::string name, int position)
    : name{name}, position{position} {}
