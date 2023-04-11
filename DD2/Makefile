CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -Werror=vla -MMD
OBJECTS = token.o info.o property.o academic.o nonacademic.o nonproperty.o money.o movement.o card.o main.o commandInterpreter.o block.o board.o textdisplay.o player.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = watopoly

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

.PHONY = clean

clean:
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}
