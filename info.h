#ifndef INFOS_H
#define INFOS_H

#include <string>

#include "state.h"

const int displayLength = 5;
const int maxImproveLevel = 5;

// Superclass Info
struct Info {
	int row, col;
	std::string name;
	std::string displayName[displayLength];
	BlockType type;
	Descriptor desc;
	Action action; // what happens when a player lands on the block
}

#endif
