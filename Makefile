INSTALL_DIR = ${HOME}/.local


CXX = g++
CXX_FLAGS = -O0 -g -std=c++11
#CXX_FLAGS = -O3 -std=c++11
LDFLAGS = -lm

SHOW_MATRIX_SOURCES = show-matrix.cpp

HEADERS = matrices/DenseMatrix.h

SOURCES = $(SHOW_MATRIX_SOURCES)

DIST = $(SOURCES) $(HEADERS) Makefile

     
all: show-matrix 

show-matrix: show-matrix.o CommandLineParser.o matrices/DenseMatrix.o string-split.o bin
	$(CXX) -o bin/$@ show-matrix.o CommandLineParser.o string-split.o matrices/DenseMatrix.o $(LDFLAGS)

bin:
	mkdir bin

install: all
	mkdir -p $(INSTALL_DIR)/bin
	cp bin/* $(INSTALL_DIR)/bin

clean:
	rm -f *.o

dist: $(DIST)
	tar zcvf fjfi-01num1-src.tgz $(DIST)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXX_FLAGS) -c -o $@ $<
