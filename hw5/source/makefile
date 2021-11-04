cwd = ${HOME}/molecular_simulation/hw5
BIN=$(cwd)/bin
OBJS = main.o initialize.o force_energy.o kin_energy.o mdrun.o neighbor.o parameters.o pos_distance.o read_in.o
TARGET = main
CXX = g++
INCL=-I${cwd}/source
.cpp.o:
	${CXX} -std=c++11 ${INCL} -c $<
${TARGET}:${OBJS}
	${CXX} -o $@ $?
	rm ${OBJS}
	mv $@ ${BIN}
clean:
	rm ${BIN}/main