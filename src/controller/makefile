CC=g++
CFLAGS=-W -Wall -ansi -pedantic -I ../../include/
LDPATH=/lib/
SRC= $(wildcard *.cpp)
OBJ= $(SRC:.cpp=.o)

all: $(OBJ)

%.o: %.cpp
	$(CC) -o ../../bin/controller_$@ -c $< $(CFLAGS) -L$(LDPATH)

.PHONY: clean

clean:
	rm ../../bin/*.o
