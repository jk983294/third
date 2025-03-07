# compile each cpp file into separate executable

SHELL = /bin/sh

# CXXFLAGS = -std=c++17 -Wall -g -pthread
CXXFLAGS = -std=c++17 -Wall -O3 -pthread
CXX = g++
INCLUDES = -I/opt/3rd/ortools/include
LDFLAGS = -L/opt/3rd/ortools/lib/ -Wl,-rpath=/opt/3rd/ortools/lib/
LDLIBS = -lortools

TARGETS = $(patsubst %.cpp, %, $(wildcard *.cpp))

all: $(TARGETS)

%: %.cpp
	${CXX} ${CXXFLAGS} ${INCLUDES} ${LDFLAGS} $^ -o $@ ${LDLIBS}

%.o: %.cpp
	${CXX} ${CXXFLAGS} ${INCLUDES} -c $< -o $@

clean:
	-rm -f *.o ${TARGETS}

.PHONY: all clean