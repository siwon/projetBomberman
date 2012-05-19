CC=g++
CFLAGS=-W -Wall -ansi -pedantic -I ../../include/
SRC= $(wildcard *.cpp)
OBJ= $(SRC:.cpp=.o)

all: $(OBJ)

%.o: %.cpp
	$(CC) -o ../../bin/configFile_$@ -c $< $(CFLAGS)

.PHONY: clean

clean:
	rm ../../bin/*.o
