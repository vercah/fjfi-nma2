TARGETS += riccati hyperbolic species lorenz nbody

CXX_FLAGS += -Iode
 
RICCATI_OBJECTS = ode/riccati.o

RICCATI_SOURCES = ode/riccati.cpp

HYPERBOLIC_OBJECTS = ode/hyperbolic.o

HYPERBOLIC_SOURCES = ode/hyperbolic.cpp

SPECIES_OBJECTS = ode/species.o

SPECIES_SOURCES = ode/species.cpp

LORENZ_OBJECTS = ode/lorenz.o

LORENZ_SOURCES = ode/lorenz.cpp

NBODY_OBJECTS = ode/nbody.o

NBODY_SOURCES = ode/nbody.cpp


OBJECTS += $(RICCATI_OBJECTS) \
           $(HYPERBOLIC_OBJECTS) \
           $(SPECIES_OBJECTS) \
           $(LORENZ_OBJECTS) \
	   $(NBODY_OBJECTS)

SOURCES += $(RICCATI_SOURCES) \
           $(HYPERBOLIC_SOURCES) \
           $(SPECIES_SOURCES) \
           $(LORENZ_SOURCES) \
	   $(NBODY_SOURCES)

HEADERS += ode/Euler.h \
           ode/HyperbolicProblem.h  \
           ode/IntegratorBase.h \
           ode/LorenzProblem.h \
           ode/Merson.h \
           ode/ODESolution.h \
           ode/ODESolver.h \
           ode/RiccatiProblem.h \
           ode/SpeciesProblem.h

     
MAKEFILES += ode/Makefile

riccati: $(RICCATI_OBJECTS) $(RICCATI_SOURCES) $(HEADERS)
	$(CXX) $(RICCATI_OBJECTS) $(LD_FLAGS) -o bin/riccati

hyperbolic: $(HYPERBOLIC_OBJECTS) $(HYPERBOLIC_SOURCES) $(HEADERS)
	$(CXX) $(HYPERBOLIC_OBJECTS) $(LD_FLAGS) -o bin/hyperbolic
	
species: $(SPECIES_OBJECTS) $(SPECIES_SOURCES) $(HEADERS)
	$(CXX) $(SPECIES_OBJECTS) $(LD_FLAGS) -o bin/species
	
lorenz: $(LORENZ_OBJECTS) $(LORENZ_SOURCES) $(HEADERS)
	$(CXX) $(LORENZ_OBJECTS) $(LD_FLAGS) -o bin/lorenz
	
nbody: $(NBODY_OBJECTS) $(NBODY_SOURCES) $(HEADERS)
	$(CXX) $(NBODY_OBJECTS) $(LD_FLAGS) -o bin/nbody
	
%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXX_FLAGS) -c -o $@ $<	
