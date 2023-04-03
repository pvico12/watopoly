#ifndef STATE_H
#define STATE_H

#include <vector>

enum class StateType { NewVisitor, VisitorLeft };
enum class BlockType { Property, NonProperty }
enum class Descriptor { Academic, Residence, Gym, Money, Move, ChancePay, ChanceMove }; // add JAIL
enum class Action { Buy, Improve, PayOwner, PayBank, Collect, Move } // add JAIL


struct State {
	StateType type;
	std::vector<Player*> visitors;
}

#endif
