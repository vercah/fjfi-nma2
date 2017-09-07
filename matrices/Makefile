include ../Makefile.inc

TARGETS = show-matrix \
          ellpack-test

COMMON_OBJECTS = ../CommandLineParser.o \
                 ../string-split.o \
                 ../Timer.o \
                 ../Vector.o \
                 ../matrices/Matrix.o

SHOW_MATRIX_OBJECTS = show-matrix.o \
                       ../matrices/DenseMatrix.o

ELLPACK_TEST_OBJECTS = ../matrices/DenseMatrix.o \
                       ../matrices/EllpackMatrix.o \
                       ellpack-test.o

$(shell mkdir -p $(DEPDIR) >/dev/null)

all: $(TARGETS)

show-matrix: $(SHOW_MATRIX_OBJECTS) $(COMMON_OBJECTS)
	$(CXX) -o $@ $(SHOW_MATRIX_OBJECTS) $(COMMON_OBJECTS) $(LDFLAGS)
	cp show-matrix ../bin
	
ellpack-test: $(ELLPACK_TEST_OBJECTS) $(COMMON_OBJECTS)
	$(CXX) -o $@ $(ELLPACK_TEST_OBJECTS) $(COMMON_OBJECTS) $(LDFLAGS)
	cp ellpack-test ../bin
	
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