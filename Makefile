INSTALL_DIR = ${HOME}/.local


CXX = g++
CXX_FLAGS = -O0 -g -std=c++11
#CXX_FLAGS = -O3 -std=c++11
LDFLAGS = -lm

COMMON_SOURCES = CommandLineParser.cpp \
                 string-split.cpp \
                 Vector.cpp \
                 matrices/Matrix.cpp

COMMON_OBJECTS = CommandLineParser.o \
                 string-split.o \
                 Vector.o \
                 matrices/Matrix.o

SHOW_MATRIX_SOURCES = show-matrix.cpp

HEADERS = matrices/DenseMatrix.h

SOURCES = $(SHOW_MATRIX_SOURCES)

DIST = $(SOURCES) $(HEADERS) Makefile

     
all: show-matrix gem-test

show-matrix: $(COMMON_OBJECTS) show-matrix.o matrices/DenseMatrix.o bin
	$(CXX) -o bin/$@ show-matrix.o matrices/DenseMatrix.o $(COMMON_OBJECTS) $(LDFLAGS)

gem-test: $(COMMON_OBJECTS) matrices/DenseMatrix.o GEM.o gem-test.o bin
	$(CXX) -o bin/$@ gem-test.o GEM.o matrices/DenseMatrix.o $(COMMON_OBJECTS) $(LDFLAGS)

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
