CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -Werror=vla -MMD
OBJECTS = main.o subject.o observer.o block.o board.o textdisplay.o Property/property.o Property/academic.o Property/nonacademic.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = Watopoly

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

.PHONY = clean

clean:
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}
