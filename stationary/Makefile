include ../Makefile.inc

TARGETS = stationary-solver

COMMON_SOURCES = ../CommandLineParser.cpp \
                 ../string-split.cpp \
                 ../Timer.cpp \
                 ../Vector.cpp \
                 ../matrices/Matrix.cpp

SOURCES = $(COMMON_SOURCES) \
	  StationarySolver.cpp \
	  stationary-solver.cpp

COMMON_OBJECTS = ../CommandLineParser.o \
                 ../string-split.o \
                 ../Timer.o \
                 ../Vector.o \
                 ../matrices/Matrix.o

STATIONARY_SOLVER_OBJECTS = ../matrices/DenseMatrix.o \
                            ../matrices/EllpackMatrix.o \
                            StationarySolver.o \
                            stationary-solver.o

all: $(TARGETS)

stationary-solver: $(STATIONARY_SOLVER_OBJECTS) $(COMMON_OBJECTS) 
	$(CXX) -o $@ $(STATIONARY_SOLVER_OBJECTS) $(COMMON_OBJECTS) $(LDFLAGS)
	cp stationary-solver ../bin
	
.PHONY: clean
clean:
	rm -f *.o *.d $(TARGETS)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<	

$(SOURCES:%.cpp=%.o): %.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
	
-include $(SOURCES:%.cpp=%.d)