CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -Werror=vla -MMD
OBJECTS = main.o player.o board.o display.o block.o property.o nonproperty.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = Watopoly

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean:
	rm -f ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}
