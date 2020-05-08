XX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla
EXEC = biquadris
OBJECTS = grid.o info.o textdisplay.o cell.o subject.o observer.o block/block.o game.o level/level.o level/level1.o level/level2.o block/iblock.o main.o block/jblock.o block/lblock.o block/oblock.o block/zblock.o block/sblock.o block/tblock.o level/level0.o level/level3.o level/level4.o block/gblock.o player.o graphicsdisplay.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
				${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
				rm ${OBJECTS} ${EXEC} ${DEPENDS}
