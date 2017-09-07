include ../Makefile.inc

TARGETS = gem-solver lu-test lu-solver thomas-solver

COMMON_OBJECTS = ../CommandLineParser.o \
                 ../string-split.o \
                 ../Timer.o \
                 ../Vector.o \
                 ../matrices/Matrix.o

GEM_SOLVER_OBJECTS = ../matrices/DenseMatrix.o \
                     GEM.o \
                     gem-solver.o

LU_TEST_OBJECTS = ../matrices/DenseMatrix.o \
                  LUDecomposition.o \
                  lu-test.o

LU_SOLVER_OBJECTS = ../matrices/DenseMatrix.o \
                    LUDecomposition.o \
                    lu-solver.o

THOMAS_SOLVER_OBJECTS = ../matrices/DenseMatrix.o \
                        ../matrices/TridiagonalMatrix.o \
                        ThomasAlgorithm.o \
                        GEM.o \
                        thomas-solver.o

$(shell mkdir -p $(DEPDIR) >/dev/null)

all: $(TARGETS)

gem-solver: $(GEM_SOLVER_OBJECTS) $(COMMON_OBJECTS)
	$(CXX) -o $@ $(GEM_SOLVER_OBJECTS) $(COMMON_OBJECTS) $(LDFLAGS)
	cp gem-solver ../bin

lu-test: $(LU_TEST_OBJECTS) $(COMMON_OBJECTS)
	$(CXX) -o $@ $(LU_TEST_OBJECTS) $(COMMON_OBJECTS) $(LDFLAGS)
	cp lu-test ../bin

lu-solver: $(LU_SOLVER_OBJECTS) $(COMMON_OBJECTS)
	$(CXX) -o $@ $(LU_SOLVER_OBJECTS) $(COMMON_OBJECTS) $(LDFLAGS)
	cp lu-solver ../bin

thomas-solver:  $(THOMAS_SOLVER_OBJECTS) $(COMMON_OBJECTS)
	$(CXX) -o $@ $(THOMAS_SOLVER_OBJECTS) $(COMMON_OBJECTS) $(LDFLAGS)
	cp thomas-solver ../bin

.PHONY: clean
clean:
	rm -f *.o $(TARGETS)
	
%.o: %.cpp
%.o: %.cpp $(DEPDIR)/%.d
	$(COMPILE.cxx) $(OUTPUT_OPTION) $<
	$(POSTCOMPILE)
	$(CXX) $(CPPFLAGS) $(CXX_FLAGS) -c -o $@ $<	

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d
	
include $(wildcard $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS))))