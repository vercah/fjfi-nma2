TARGETS += riccati \
           hyperbolic

CXX_FLAGS += -Iode
 
RICCATI_OBJECTS = ode/riccati.o

RICCATI_SOURCES = ode/riccati.cpp

HYPERBOLIC_OBJECTS = ode/hyperbolic.o

HYPERBOLIC_SOURCES = ode/hyperbolic.cpp


OBJECTS += $(RICCATI_OBJECTS) \
           $(HYPERBOLIC_OBJECTS) 

SOURCES += $(RICCATI_SOURCES) \
           $(HYPERBOLIC_SOURCES) 

MAKEFILES += ode/Makefile

riccati: $(RICCATI_OBJECTS)
	$(CXX) $(RICCATI_OBJECTS) $(LD_FLAGS) -o riccati

hyperbolic: $(HYPERBOLIC_OBJECTS)
	$(CXX) $(HYPERBOLIC_OBJECTS) $(LD_FLAGS) -o hyperbolic
	