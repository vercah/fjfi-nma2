include ../Makefile.inc

TARGETS = poisson-1d \
	  poisson-2d \
	  heat-equation-1d \
	  heat-equation-2d \
	  implicit-heat-equation-1d \
	  implicit-heat-equation-2d \
	  perona-malik-1d \
	  perona-malik-2d \
	  semi-implicit-perona-malik-1d

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
	  heat-equation-2d.cpp \
	  implicit-heat-equation-1d.cpp \
	  implicit-heat-equation-2d.cpp \
	  perona-malik-1d.cpp \
	  perona-malik-2d.cpp \
	  semi-implicit-perona-malik-1d.cpp
	
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
IMPLICT_HEAT_EQUATION_1D_OBJECTS = $(COMMON_OBJECTS) implicit-heat-equation-1d.o HeatEquationProblem1D.o
IMPLICT_HEAT_EQUATION_2D_OBJECTS = $(COMMON_OBJECTS) implicit-heat-equation-2d.o HeatEquationProblem2D.o
PERONA_MALIK_1D_OBJECTS = $(COMMON_OBJECTS) perona-malik-1d.o PeronaMalikProblem1D.o
PERONA_MALIK_2D_OBJECTS = $(COMMON_OBJECTS) perona-malik-2d.o PeronaMalikProblem2D.o
SEMI_IMPLICT_PERONA_MALIK_1D_OBJECTS = $(COMMON_OBJECTS) semi-implicit-perona-malik-1d.o PeronaMalikProblem1D.o

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

implicit-heat-equation-1d: $(IMPLICT_HEAT_EQUATION_1D_OBJECTS)
	$(CXX) -o $@ $(IMPLICT_HEAT_EQUATION_1D_OBJECTS) $(LD_FLAGS)
	cp implicit-heat-equation-1d ../bin

implicit-heat-equation-2d: $(IMPLICT_HEAT_EQUATION_2D_OBJECTS)
	$(CXX) -o $@ $(IMPLICT_HEAT_EQUATION_2D_OBJECTS) $(LD_FLAGS)
	cp implicit-heat-equation-2d ../bin

perona-malik-1d: $(PERONA_MALIK_1D_OBJECTS)
	$(CXX) -o $@ $(PERONA_MALIK_1D_OBJECTS) $(LD_FLAGS)
	cp perona-malik-1d ../bin

perona-malik-2d: $(PERONA_MALIK_2D_OBJECTS)
	$(CXX) -o $@ $(PERONA_MALIK_2D_OBJECTS) $(LD_FLAGS)
	cp perona-malik-2d ../bin

semi-implicit-perona-malik-1d: $(SEMI_IMPLICT_PERONA_MALIK_1D_OBJECTS)
	$(CXX) -o $@ $(SEMI_IMPLICT_PERONA_MALIK_1D_OBJECTS) $(LD_FLAGS)
	cp semi-implicit-perona-malik-1d ../bin


.PHONY: clean
clean:
	rm -f *.o *.d $(TARGETS)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<	

$(SOURCES:%.cpp=%.o): %.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
	
-include $(SOURCES:%.cpp=%.d)	