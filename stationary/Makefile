include ../Makefile.inc

TARGETS = stationary-solver

COMMON_OBJECTS = ../CommandLineParser.o \
                 ../string-split.o \
                 ../Timer.o \
                 ../Vector.o \
                 ../matrices/Matrix.o

STATIONARY_SOLVER_OBJECTS = ../matrices/DenseMatrix.o \
                            ../matrices/EllpackMatrix.o \
                            StationarySolver.o \
                            stationary-solver.o

$(shell mkdir -p $(DEPDIR) >/dev/null)

all: $(TARGETS)

stationary-solver: $(STATIONARY_SOLVER_OBJECTS) $(COMMON_OBJECTS) 
	$(CXX) -o $@ $(STATIONARY_SOLVER_OBJECTS) $(COMMON_OBJECTS) $(LDFLAGS)
	cp stationary-solver ../bin
	
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