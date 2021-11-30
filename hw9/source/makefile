BIN=../bin
OBJS = main.o initialize.o force_energy.o kin_energy.o mdrun.o neighbor.o parameters.o pos_distance.o
TARGET = main
CXX = c++
%.o:%.cpp
	${CXX} -std=c++11 -c $<
${TARGET}:${OBJS}
	${CXX} -o $@ $?
	rm ${OBJS}
	mv $@ ${BIN}
clean:
	rm ${BIN}/main