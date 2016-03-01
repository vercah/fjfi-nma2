TARGETS += riccati hyperbolic species lorentz

CXX_FLAGS += -Iode
 
RICCATI_OBJECTS = ode/riccati.o

RICCATI_SOURCES = ode/riccati.cpp

HYPERBOLIC_OBJECTS = ode/hyperbolic.o

HYPERBOLIC_SOURCES = ode/hyperbolic.cpp

SPECIES_OBJECTS = ode/species.o

SPECIES_SOURCES = ode/species.cpp

LORENTZ_OBJECTS = ode/lorentz.o

LORENTZ_SOURCES = ode/lorentz.cpp


OBJECTS += $(RICCATI_OBJECTS) \
           $(HYPERBOLIC_OBJECTS) \
           $(SPECIES_OBJECTS) \
           $(LORENTZ_OBJECTS)

SOURCES += $(RICCATI_SOURCES) \
           $(HYPERBOLIC_SOURCES) \
           $(SPECIES_SOURCES) \
           $(LORENTZ_SOURCES)

MAKEFILES += ode/Makefile

riccati: $(RICCATI_OBJECTS)
	$(CXX) $(RICCATI_OBJECTS) $(LD_FLAGS) -o riccati

hyperbolic: $(HYPERBOLIC_OBJECTS)
	$(CXX) $(HYPERBOLIC_OBJECTS) $(LD_FLAGS) -o hyperbolic
	
species: $(SPECIES_OBJECTS)
	$(CXX) $(SPECIES_OBJECTS) $(LD_FLAGS) -o species
	
lorentz: $(LORENTZ_OBJECTS)
	$(CXX) $(LORENTZ_OBJECTS) $(LD_FLAGS) -o lorentz
	