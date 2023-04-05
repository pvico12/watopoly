#ifndef STATE_H
#define STATE_H

/* State types are:
   VisitorArrived - a Player has arrived here.
   VisitorLeft - a Player has left here.
*/
enum class StateType { VisitorArrived, VisitorLeft };
enum class Desc { AcademicBuilding, NonAcademicBuilding, ChanceMove, ChancePay, Other };

struct State {
  StateType type;
  Desc desc;
};

#endif