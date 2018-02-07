include ../Makefile.inc

TARGETS = riccati hyperbolic species lorenz nbody

COMMON_SOURCES = ../CommandLineParser.cpp \
                 ../string-split.cpp \
                 ../Timer.cpp \
                 ../Vector.cpp \
                 ../matrices/Matrix.cpp

SOURCES = $(COMMON_SOURCES) \
          ricatti.cpp \
          hyperbolic.cpp \
          species.cpp \
          lorenz.cpp \
          nbody.cpp

COMMON_OBJECTS = ../CommandLineParser.o \
                 ../string-split.o \
                 ../Timer.o \
                 ../Vector.o \
                 ../matrices/Matrix.o \
                 Euler.o \
                 Merson.o \
                 RungeKutta.o
 
RICCATI_OBJECTS = $(COMMON_OBJECTS) RiccatiProblem.o riccati.o

HYPERBOLIC_OBJECTS = $(COMMON_OBJECTS) HyperbolicProblem.o hyperbolic.o

SPECIES_OBJECTS = $(COMMON_OBJECTS) SpeciesProblem.o species.o

LORENZ_OBJECTS = $(COMMON_OBJECTS) LorenzProblem.o lorenz.o

NBODY_OBJECTS = $(COMMON_OBJECTS) NBodyProblem.o nbody.o

all: $(TARGETS)

riccati: $(RICCATI_OBJECTS)
	$(CXX) -o $@ $(RICCATI_OBJECTS) $(LD_FLAGS)
	cp riccati ../bin

hyperbolic: $(HYPERBOLIC_OBJECTS)
	$(CXX) -o $@ $(HYPERBOLIC_OBJECTS) $(LD_FLAGS)
	cp hyperbolic ../bin
	
species: $(SPECIES_OBJECTS)
	$(CXX) -o $@ $(SPECIES_OBJECTS) $(LD_FLAGS)
	cp species ../bin
	
lorenz: $(LORENZ_OBJECTS)
	$(CXX) -o $@ $(LORENZ_OBJECTS) $(LD_FLAGS)
	cp lorenz ../bin
	
nbody: $(NBODY_OBJECTS)
	$(CXX) -o $@ $(NBODY_OBJECTS) $(LD_FLAGS)
	cp nbody ../bin
	
.PHONY: clean
clean:
	rm -f *.o *.d $(TARGETS)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<	

$(SOURCES:%.cpp=%.o): %.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
	
-include $(SOURCES:%.cpp=%.d)	