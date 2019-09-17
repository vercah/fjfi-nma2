include ../Makefile.inc

TARGETS = power-method \
          eigenvalues 

COMMON_SOURCES = ../CommandLineParser.cpp \
                 ../string-split.cpp \
                 ../Timer.cpp \
                 ../Vector.cpp \
                 ../matrices/Matrix.cpp \
                 eigenvectors.cpp

SOURCES = $(COMMON_SOURCES) \
          PowerMethod.cpp \
          power-method.cpp \
          TriangularMehtod.cpp \
          LRAlgorithm.cpp \
          eigenvalues.cpp

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

EIGENVALUES_OBJECTS = ../matrices/DenseMatrix.o \
                      ../matrices/TriangularOperations.o \
                      ../matrices/LUDecomposition.o \
                      TriangularMethod.o \
                      LRAlgorithm.o \
                      eigenvalues.o \
		      eigenvectors.o

all: $(TARGETS)

power-method:  $(POWER_METHOD_OBJECTS) $(COMMON_OBJECTS)
	$(CXX) -o $@  $(POWER_METHOD_OBJECTS) $(COMMON_OBJECTS) $(LDFLAGS)
	cp power-method ../bin

eigenvalues:  $(EIGENVALUES_OBJECTS) $(COMMON_OBJECTS)
	$(CXX) -o $@  $(EIGENVALUES_OBJECTS) $(COMMON_OBJECTS) $(LDFLAGS)
	cp eigenvalues ../bin

.PHONY: clean
clean:
	rm -f *.o *.d $(TARGETS)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<	

$(SOURCES:%.cpp=%.o): %.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
	
-include $(SOURCES:%.cpp=%.d)	