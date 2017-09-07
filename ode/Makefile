include ../Makefile.inc

TARGETS = riccati hyperbolic species lorenz nbody

COMMON_OBJECTS = ../CommandLineParser.o \
                 ../string-split.o \
                 ../Timer.o \
                 ../Vector.o \
                 ../matrices/Matrix.o
 
RICCATI_OBJECTS = riccati.o

HYPERBOLIC_OBJECTS = hyperbolic.o

SPECIES_OBJECTS = species.o

LORENZ_OBJECTS = lorenz.o

NBODY_OBJECTS = nbody.o

$(shell mkdir -p $(DEPDIR) >/dev/null)

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
	rm -f *.o $(TARGETS)

%.o: %.cpp
%.o: %.cpp $(DEPDIR)/%.d
	$(COMPILE.cxx) $(OUTPUT_OPTION) $<
	$(POSTCOMPILE)
	$(CXX) $(CPPFLAGS) $(CXX_FLAGS) -c -o $@ $<	

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d
	
include $(wildcard $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS))))