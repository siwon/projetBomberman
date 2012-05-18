CC=g++
CFLAGS=-W -Wall -ansi -pedantic -I ../../include/ 2>> error.log
SRC= $(wildcard *.cpp)
OBJ= $(SRC:.cpp=.o)

all: $(OBJ)

%.o: %.cpp
	$(CC) -o ../../bin/$@ -c $< $(CFLAGS)

.PHONY: clean

clean:
	rm error.log
	rm ../../bin/*.o
