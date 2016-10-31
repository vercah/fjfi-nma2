INSTALL_DIR = ${HOME}/.local


CXX = g++
CXX_FLAGS = -O0 -g -std=c++11
#CXX_FLAGS = -O3 -std=c++11
LDFLAGS = -lm

COMMON_SOURCES = CommandLineParser.cpp \
                 string-split.cpp \
                 Timer.cpp \
                 Vector.cpp \
                 matrices/Matrix.cpp

COMMON_OBJECTS = CommandLineParser.o \
                 string-split.o \
                 Timer.o \
                 Vector.o \
                 matrices/Matrix.o

SHOW_MATRIX_SOURCES = show-matrix.cpp

HEADERS = matrices/DenseMatrix.h \
          CommandLineParser.h \
          Timer.h \
          Vector.h \
          real.h \
          string-split.h

SOURCES = $(SHOW_MATRIX_SOURCES)

DIST = $(SOURCES) $(HEADERS) Makefile

     
all: show-matrix \
	gem-solver \
	lu-test \
	lu-solver \
	thomas-solver \
	stationary-solver \
	ellpack-test

show-matrix: $(COMMON_OBJECTS) show-matrix.o matrices/DenseMatrix.o bin
	$(CXX) -o bin/$@ show-matrix.o matrices/DenseMatrix.o $(COMMON_OBJECTS) $(LDFLAGS)

gem-solver: $(COMMON_OBJECTS) matrices/DenseMatrix.o gem/GEM.o gem/gem-solver.o bin
	$(CXX) -o bin/$@ gem/gem-solver.o gem/GEM.o matrices/DenseMatrix.o $(COMMON_OBJECTS) $(LDFLAGS)

lu-test: $(COMMON_OBJECTS) matrices/DenseMatrix.o gem/LUDecomposition.o gem/lu-test.o bin
	$(CXX) -o bin/$@ gem/lu-test.o gem/LUDecomposition.o matrices/DenseMatrix.o $(COMMON_OBJECTS) $(LDFLAGS)

lu-solver: $(COMMON_OBJECTS) matrices/DenseMatrix.o gem/LUDecomposition.o gem/lu-solver.o bin
	$(CXX) -o bin/$@ gem/lu-solver.o gem/LUDecomposition.o matrices/DenseMatrix.o $(COMMON_OBJECTS) $(LDFLAGS)

thomas-solver: matrices/DenseMatrix.o matrices/TridiagonalMatrix.o gem/ThomasAlgorithm.o gem/GEM.o gem/thomas-solver.o $(COMMON_OBJECTS) bin
	$(CXX) -o bin/$@ matrices/DenseMatrix.o matrices/TridiagonalMatrix.o gem/ThomasAlgorithm.o gem/GEM.o gem/thomas-solver.o $(COMMON_OBJECTS) $(LDFLAGS)

stationary-solver: matrices/DenseMatrix.o stationary/StationarySolver.o stationary/stationary-solver.o $(COMMON_OBJECTS) bin
	$(CXX) -o bin/$@ matrices/DenseMatrix.o stationary/StationarySolver.o stationary/stationary-solver.o $(COMMON_OBJECTS) $(LDFLAGS)

ellpack-test: matrices/DenseMatrix.o matrices/EllpackMatrix.o matrices/ellpack-test.o $(COMMON_OBJECTS) bin
	$(CXX) -o bin/$@ matrices/DenseMatrix.o matrices/EllpackMatrix.o matrices/ellpack-test.o $(COMMON_OBJECTS) $(LDFLAGS)

bin:
	mkdir bin

install: all
	mkdir -p $(INSTALL_DIR)/bin
	cp bin/* $(INSTALL_DIR)/bin

clean:
	rm -f *.o matrices/*.o gem/*.o stationary/*.o

dist: $(DIST)
	tar zcvf fjfi-01num1-src.tgz $(DIST)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXX_FLAGS) -c -o $@ $<
