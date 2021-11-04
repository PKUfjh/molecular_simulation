cwd = ${HOME}/molecular_simulation/hw3
BIN=$(cwd)/bin
OBJS = main.o initialize.o neighbor.o parameters.o pos_distance.o
TARGET = main
CXX = g++
INCL=-I${cwd}/source
.cpp.o:
	${CXX} ${INCL} -c $<
${TARGET}:${OBJS}
	${CXX} -o $@ $?
	rm ${OBJS}
	mv $@ ${BIN}
clean:
	rm ${BIN}/main