CXX = g++
CXXFLAGS = -std=c++14 -Wall -g -Werror=vla -I/usr/X11R6/include/
OBJECTS = main.o cell.o blocks.o iblock.o jblock.o lblock.o oblock.o sblock.o tblock.o zblock.o starblock.o board.o levels.o score.o player.o commander.o displayobserver.o textdisplay.o window.o graphicsdisplay.o controller.o
EXEC = biquadris
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -L/usr/X11R6/lib -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${EXEC} ${OBJECTS}
