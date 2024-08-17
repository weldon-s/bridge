CXX=g++
CXXFLAGS=-std=c++20 -Wall -g -MMD -I .
EXEC=bridge
CCFILES=$(wildcard *.cc) $(wildcard **/*.cc)
OBJECTS=${CCFILES:.cc=.o}
DEPENDS = ${OBJECTS:.o=.d}
${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}
-include ${DEPENDS}

PHONY: clean run
clean:
	rm ${EXEC} ${OBJECTS} ${DEPENDS}
