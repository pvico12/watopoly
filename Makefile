CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -Werror=vla -MMD
OBJECTS = token.o info.o Property/property.o Property/academic.o Property/nonacademic.o NonProperty/nonproperty.o NonProperty/money.o NonProperty/movement.o NonProperty/card.o main.o commandInterpreter.o block.o board.o textdisplay.o player.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = watopoly

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

.PHONY = clean

clean:
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}
