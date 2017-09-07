include ../Makefile.inc

TARGETS = power-method

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

COMMON_SOURCES = ../CommandLineParser.cpp \
                 ../string-split.cpp \
                 ../Timer.cpp \
                 ../Vector.cpp \
                 ../matrices/Matrix.cpp


SOURCES = $(COMMON_SOURCES) \
        ../matrices/DenseMatrix.cpp \
                       ../matrices/EllpackMatrix.cpp \
                       ../stationary/StationarySolver.cpp \
                       PowerMethod.cpp \
                       power-method.cpp

all: $(TARGETS)

power-method:  $(POWER_METHOD_OBJECTS) $(COMMON_OBJECTS)
	$(CXX) -o $@  $(POWER_METHOD_OBJECTS) $(COMMON_OBJECTS) $(LDFLAGS)
	cp power-method ../bin
	
.PHONY: clean
clean:
	rm -f *.o $(TARGETS)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<	

$(SOURCES:%.cpp=%.o): %.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
	
-include $(SOURCES:%.cpp=%.d)	