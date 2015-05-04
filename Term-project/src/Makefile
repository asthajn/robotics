CXX=g++
DEBUG=-g3
CXXFLAGS+=${DEBUG} -O3 -Wall -Wextra -c -std=gnu++11 `pkg-config --cflags --libs cairo gtk+-2.0`
LDFLAGS+=-std=gnu++11 `pkg-config --cflags --libs cairo gtk+-2.0`
EXEC=pRRTPath
SRC=$(wildcard *.cpp)
OBJ= $(SRC:.cpp=.o)
INC=$(wildcard *.h)

ARC=PorcelNicolas.zip
DIST=$(SRC) $(INC) README Makefile

all: $(EXEC)

pRRTPath: $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) -o $@ $< $(CXXFLAGS)

MainFile.o: GridMap.h GraphEdge.h Path.h gtype.h
GridMap.o: GridMap.h
GraphEdge.o: GraphEdge.h
Path.o: Path.h
gtype.o: gtype.h

dist:
	zip $(ARC) $(DIST)

.PHONY: clean mrproper

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC) $(ARC)
