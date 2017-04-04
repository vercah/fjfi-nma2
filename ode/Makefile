TARGETS += riccati hyperbolic species lorentz nbody

CXX_FLAGS += -Iode
 
RICCATI_OBJECTS = ode/riccati.o

RICCATI_SOURCES = ode/riccati.cpp

HYPERBOLIC_OBJECTS = ode/hyperbolic.o

HYPERBOLIC_SOURCES = ode/hyperbolic.cpp

SPECIES_OBJECTS = ode/species.o

SPECIES_SOURCES = ode/species.cpp

LORENTZ_OBJECTS = ode/lorentz.o

LORENTZ_SOURCES = ode/lorentz.cpp

NBODY_OBJECTS = ode/nbody.o

NBODY_SOURCES = ode/nbody.cpp


OBJECTS += $(RICCATI_OBJECTS) \
           $(HYPERBOLIC_OBJECTS) \
           $(SPECIES_OBJECTS) \
           $(LORENTZ_OBJECTS) \
	   $(NBODY_OBJECTS)

SOURCES += $(RICCATI_SOURCES) \
           $(HYPERBOLIC_SOURCES) \
           $(SPECIES_SOURCES) \
           $(LORENTZ_SOURCES) \
	   $(NBODY_SOURCES)

HEADERS += ode/Euler.h \
           ode/HyperbolicProblem.h  \
           ode/IntegratorBase.h \
           ode/LorentzProblem.h \
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
	
lorentz: $(LORENTZ_OBJECTS) $(LORENTZ_SOURCES) $(HEADERS)
	$(CXX) $(LORENTZ_OBJECTS) $(LD_FLAGS) -o bin/lorentz
	
nbody: $(NBODY_OBJECTS) $(NBODY_SOURCES) $(HEADERS)
	$(CXX) $(NBODY_OBJECTS) $(LD_FLAGS) -o bin/nbody
	
%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXX_FLAGS) -c -o $@ $<	
