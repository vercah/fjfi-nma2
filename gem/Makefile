include ../Makefile.inc

TARGETS = gem-solver lu-solver thomas-solver

COMMON_SOURCES = ../CommandLineParser.cpp \
                 ../string-split.cpp \
                 ../Timer.cpp \
                 ../Vector.cpp \
                 ../matrices/Matrix.cpp

SOURCES = $(COMMON_SOURCES) \
         ../matrices/DenseMatrix.cpp \
         ../matrices/TridiagonalMatrix.cpp \
	GEM.cpp \
	gem-solver.cpp \
	LUDecomposition.cpp \
	lu-test.cpp \
        lu-solver.cpp \
        ThomasAlgorithm.cpp \
        thomas-solver.cpp

COMMON_OBJECTS = ../CommandLineParser.o \
                 ../string-split.o \
                 ../Timer.o \
                 ../Vector.o \
                 ../matrices/Matrix.o

GEM_SOLVER_OBJECTS = ../matrices/DenseMatrix.o \
                     GEM.o \
                     gem-solver.o

LU_SOLVER_OBJECTS = ../matrices/DenseMatrix.o \
                    ../matrices/LUDecomposition.o \
                    lu-solver.o

THOMAS_SOLVER_OBJECTS = ../matrices/DenseMatrix.o \
                        ../matrices/TridiagonalMatrix.o \
                        ThomasAlgorithm.o \
                        GEM.o \
                        thomas-solver.o

all: $(TARGETS)

depend: .depend

.depend: $(SOURCES) $(HEADERS)
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^ -MF  ./.depend;

gem-solver: $(GEM_SOLVER_OBJECTS) $(COMMON_OBJECTS)
	$(CXX) -o $@ $(GEM_SOLVER_OBJECTS) $(COMMON_OBJECTS) $(LDFLAGS)
	cp gem-solver ../bin

lu-solver: $(LU_SOLVER_OBJECTS) $(COMMON_OBJECTS)
	$(CXX) -o $@ $(LU_SOLVER_OBJECTS) $(COMMON_OBJECTS) $(LDFLAGS)
	cp lu-solver ../bin

thomas-solver:  $(THOMAS_SOLVER_OBJECTS) $(COMMON_OBJECTS)
	$(CXX) -o $@ $(THOMAS_SOLVER_OBJECTS) $(COMMON_OBJECTS) $(LDFLAGS)
	cp thomas-solver ../bin

.PHONY: clean
clean:
	rm -f *.o *.d $(TARGETS)
	
%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<	

$(SOURCES:%.cpp=%.o): %.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
	
-include $(SOURCES:%.cpp=%.d)
