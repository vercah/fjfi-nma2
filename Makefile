include Makefile.inc

HEADERS = \

SOURCES = \

OBJECTS = \

MAKEFILES = \
            Makefile \
            Makefile.inc

CXX_FLAGS += -I.

include ode/Makefile

DIST = $(SOURCES) $(HEADERS) $(MAKEFILES)

all: $(TARGETS)
		

install: all
	cp $(TARGETS) $(INSTALL_DIR)/bin
	
dist: $(DIST)
	tar zcf num2-src.tgz $(DIST) 

clean: 
	rm -f $(OBJECTS)

%.o: %.cpp
	$(CXX) -c -o $@ $(CXX_FLAGS) $<

%.o: %.cu
	$(CUDA_CXX) -c -o $@ $(CUDA_CXX_FLAGS) $<
