include ../Makefile.inc

TARGETS = power-method

COMMON_SOURCES = ../CommandLineParser.cpp \
                 ../string-split.cpp \
                 ../Timer.cpp \
                 ../Vector.cpp \
                 ../matrices/Matrix.cpp

SOURCES = $(COMMON_SOURCES) \
          PowerMethod.cpp \
          power-method.cpp

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

all: $(TARGETS)

power-method:  $(POWER_METHOD_OBJECTS) $(COMMON_OBJECTS)
	$(CXX) -o $@  $(POWER_METHOD_OBJECTS) $(COMMON_OBJECTS) $(LDFLAGS)
	cp power-method ../bin
	
.PHONY: clean
clean:
	rm -f *.o *.d $(TARGETS)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<	

$(SOURCES:%.cpp=%.o): %.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
	
-include $(SOURCES:%.cpp=%.d)	