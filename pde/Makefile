include ../Makefile.inc

TARGETS = poisson-1d \
	  poisson-2d \
	  heat-equation-1d \
	  heat-equation-2d

COMMON_SOURCES = ../CommandLineParser.cpp \
                 ../string-split.cpp \
                 ../Timer.cpp \
                 ../Vector.cpp \
                 ../matrices/Matrix.cpp \
                 ../matrices/TridiagonalMatrix.cpp \
                 ../matrices/DenseMatrix.cpp \
                 ../matrices/EllpackMatrix.cpp \
                 ../gem/ThomasAlgorithm.cpp \
                 ../gem/GEM.cpp \
                 ../ode/Euler.cpp \
                 ../ode/Merson.cpp \
                 ../stationary/StationarySolver.cpp

SOURCES = $(COMMON_SOURCES) \
	  poisson-1d.cpp \
	  poisson-2d.cpp \
	  heat-equation-1d.cpp \
	  heat-equation-2d.cpp
COMMON_OBJECTS = ../CommandLineParser.o \
                 ../string-split.o \
                 ../Timer.o \
                 ../Vector.o \
                 ../matrices/Matrix.o \
                 ../matrices/TridiagonalMatrix.o \
                 ../matrices/DenseMatrix.o \
                 ../matrices/EllpackMatrix.o \
                 ../gem/ThomasAlgorithm.o \
		 ../gem/GEM.o \
	         ../ode/Euler.o \
	         ../ode/Merson.o \
		 ../stationary/StationarySolver.o
 
POISSON_1D_OBJECTS = $(COMMON_OBJECTS) poisson-1d.o
POISSON_2D_OBJECTS = $(COMMON_OBJECTS) poisson-2d.o
HEAT_EQUATION_1D_OBJECTS = $(COMMON_OBJECTS) heat-equation-1d.o HeatEquationProblem1D.o
HEAT_EQUATION_2D_OBJECTS = $(COMMON_OBJECTS) heat-equation-2d.o HeatEquationProblem2D.o


all: $(TARGETS)

poisson-1d: $(POISSON_1D_OBJECTS)
	$(CXX) -o $@ $(POISSON_1D_OBJECTS) $(LD_FLAGS)
	cp poisson-1d ../bin
	
poisson-2d: $(POISSON_2D_OBJECTS)
	$(CXX) -o $@ $(POISSON_2D_OBJECTS) $(LD_FLAGS)
	cp poisson-2d ../bin

heat-equation-1d: $(HEAT_EQUATION_1D_OBJECTS)
	$(CXX) -o $@ $(HEAT_EQUATION_1D_OBJECTS) $(LD_FLAGS)
	cp heat-equation-1d ../bin

heat-equation-2d: $(HEAT_EQUATION_2D_OBJECTS)
	$(CXX) -o $@ $(HEAT_EQUATION_2D_OBJECTS) $(LD_FLAGS)
	cp heat-equation-2d ../bin


.PHONY: clean
clean:
	rm -f *.o *.d $(TARGETS)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<	

$(SOURCES:%.cpp=%.o): %.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
	
-include $(SOURCES:%.cpp=%.d)	