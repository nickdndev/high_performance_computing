CC=g++
STD=c++17
OPTIMIZE=
CFLAGS=-c
MAIN=main.cpp
SOURCES=matrix.cpp
OBJECTS=$(SOURCES:.cpp=.o)
STATIC_LIB=matrix_lib.a
EXECUTABLE=matrix_multiplication

all: matrix

matrix:
	$(CC) $(OPTIMIZE) $(CFLAGS) $(SOURCES)
	ar rc $(STATIC_LIB) $(OBJECTS)
	$(CC) -std=$(STD) $(MAIN) $(STATIC_LIB) -o $(EXECUTABLE)
	rm *.o *.a


clean:
	rm -rf *.o $(EXECUTABLE)