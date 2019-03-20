include ../Makefile.inc

TARGETS = poisson-1d

COMMON_SOURCES = ../CommandLineParser.cpp \
                 ../string-split.cpp \
                 ../Timer.cpp \
                 ../Vector.cpp \
                 ../matrices/Matrix.cpp \
                 ../matrices/TridiagonalMatrix.cpp \
                 ../matrices/DenseMatrix.cpp \
                 ../gem/ThomasAlgorithm.cpp \
                  ../gem/GEM.cpp \
                 ../stationary/StationarySolver.cpp

SOURCES = $(COMMON_SOURCES) \
	  poisson-1d.cpp
COMMON_OBJECTS = ../CommandLineParser.o \
                 ../string-split.o \
                 ../Timer.o \
                 ../Vector.o \
                 ../matrices/Matrix.o \
                 ../matrices/TridiagonalMatrix.o \
                 ../matrices/DenseMatrix.o \
                 ../gem/ThomasAlgorithm.o \
		 ../gem/GEM.o \
		 ../stationary/StationarySolver.o
 
POISSON_1D_OBJECTS = $(COMMON_OBJECTS) poisson-1d.o


all: $(TARGETS)

poisson-1d: $(POISSON_1D_OBJECTS)
	$(CXX) -o $@ $(POISSON_1D_OBJECTS) $(LD_FLAGS)
	cp poisson-1d ../bin
	
.PHONY: clean
clean:
	rm -f *.o *.d $(TARGETS)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<	

$(SOURCES:%.cpp=%.o): %.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
	
-include $(SOURCES:%.cpp=%.d)	