CC=g++
CFLAGS=-W -Wall -ansi -pedantic -I ../../include/
SRC= $(wildcard *.cpp)
OBJ= $(SRC:.cpp=.o)

all: $(OBJ)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)
	cp *.o ../../bin

.PHONY: clean

clean:
	-rm *.o
