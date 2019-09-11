include ../Makefile.inc

TARGETS = power-method \
          triangular-method \
          lr-algorithm

COMMON_SOURCES = ../CommandLineParser.cpp \
                 ../string-split.cpp \
                 ../Timer.cpp \
                 ../Vector.cpp \
                 ../matrices/Matrix.cpp

SOURCES = $(COMMON_SOURCES) \
          PowerMethod.cpp \
          power-method.cpp \
          TriangularMehtod.cpp \
          triangular-method.cpp

COMMON_OBJECTS = ../CommandLineParser.o \
                 ../string-split.o \
                 ../Timer.o \
                 ../Vector.o \
                 ../matrices/Matrix.o

POWER_METHOD_OBJECTS = ../matrices/DenseMatrix.o \
                       ../matrices/EllpackMatrix.o \
                       ../stationary/StationarySolver.o \
                       PowerMethod.o \
                       power-method.o

TRIANGULAR_METHOD_OBJECTS = ../matrices/DenseMatrix.o \
                            ../matrices/TriangularOperations.o \
                            ../gem/LUDecomposition.o \
                            TriangularMethod.o \
                            triangular-method.o

LR_ALGORITHM_OBJECTS = ../matrices/DenseMatrix.o \
                       ../matrices/TriangularOperations.o \
                       ../gem/LUDecomposition.o \
                        LRAlgorithm.o \
                        lr-algorithm.o

all: $(TARGETS)

power-method:  $(POWER_METHOD_OBJECTS) $(COMMON_OBJECTS)
	$(CXX) -o $@  $(POWER_METHOD_OBJECTS) $(COMMON_OBJECTS) $(LDFLAGS)
	cp power-method ../bin

triangular-method:  $(TRIANGULAR_METHOD_OBJECTS) $(COMMON_OBJECTS)
	$(CXX) -o $@  $(TRIANGULAR_METHOD_OBJECTS) $(COMMON_OBJECTS) $(LDFLAGS)
	cp triangular-method ../bin

lr-algorithm:  $(LR_ALGORITHM_OBJECTS) $(COMMON_OBJECTS)
	$(CXX) -o $@  $(LR_ALGORITHM_OBJECTS) $(COMMON_OBJECTS) $(LDFLAGS)
	cp lr-algorithm ../bin

.PHONY: clean
clean:
	rm -f *.o *.d $(TARGETS)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<	

$(SOURCES:%.cpp=%.o): %.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
	
-include $(SOURCES:%.cpp=%.d)	