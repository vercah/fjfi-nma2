include ../Makefile.inc

TARGETS = show-matrix \
          ellpack-test \
          lu-test \
	  qr-test

COMMON_SOURCES = ../CommandLineParser.cpp \
                 ../string-split.cpp \
                 ../Timer.cpp \
                 ../Vector.cpp \
                 ../matrices/Matrix.cpp

SOURCES = $(COMMON_SOURCES) \
         DenseMatrix.cpp \
         EllpackMatrix.cpp \
         show-matrix.cpp \
         ellpack-test.cpp

COMMON_OBJECTS = ../CommandLineParser.o \
                 ../string-split.o \
                 ../Timer.o \
                 ../Vector.o \
                 ../matrices/Matrix.o

SHOW_MATRIX_OBJECTS = show-matrix.o \
                       DenseMatrix.o

ELLPACK_TEST_OBJECTS = DenseMatrix.o \
                       EllpackMatrix.o \
                       ellpack-test.o

LU_TEST_OBJECTS = DenseMatrix.o \
                  LUDecomposition.o \
                  lu-test.o

QR_TEST_OBJECTS = DenseMatrix.o \
                  QRDecomposition.o \
		  GrammSchmidt.o \
                  HouseholderTransformation.o \
		  GivensRotation.o \
                  qr-test.o


all: $(TARGETS)

show-matrix: $(SHOW_MATRIX_OBJECTS) $(COMMON_OBJECTS)
	$(CXX) -o $@ $(SHOW_MATRIX_OBJECTS) $(COMMON_OBJECTS) $(LDFLAGS)
	cp show-matrix ../bin
	
ellpack-test: $(ELLPACK_TEST_OBJECTS) $(COMMON_OBJECTS)
	$(CXX) -o $@ $(ELLPACK_TEST_OBJECTS) $(COMMON_OBJECTS) $(LDFLAGS)
	cp ellpack-test ../bin

lu-test: $(LU_TEST_OBJECTS) $(COMMON_OBJECTS)
	$(CXX) -o $@ $(LU_TEST_OBJECTS) $(COMMON_OBJECTS) $(LDFLAGS)
	cp lu-test ../bin

qr-test: $(QR_TEST_OBJECTS) $(COMMON_OBJECTS)
	$(CXX) -o $@ $(QR_TEST_OBJECTS) $(COMMON_OBJECTS) $(LDFLAGS)
	cp qr-test ../bin

.PHONY: clean
clean:
	rm -f *.o *.d $(TARGETS)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

$(SOURCES:%.cpp=%.o): %.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
	
-include $(SOURCES:%.cpp=%.d)	