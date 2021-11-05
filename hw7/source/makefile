cwd = ${HOME}/molecular_simulation/hw7
BIN=$(cwd)/bin
OBJS = main.o initialize.o force_energy.o kin_energy.o mdrun.o neighbor.o parameters.o pos_distance.o
TARGET = main
CXX = g++
INCL=-I${cwd}/source
%.o:%.cpp
	${CXX} -std=c++11 ${INCL} -c $<
${TARGET}:${OBJS}
	${CXX} -o $@ $?
	rm ${OBJS}
	mv $@ ${BIN}
clean:
	rm ${BIN}/main