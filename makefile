CC=g++
CFLAGS=-W -Wall -ansi -pedantic -I include/
LDFLAGS=
EXEC=PolyBomber

all: $(EXEC)

PolyBomber: main.o PolyBomberApp.o PolyBomberException.o menu
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: src/%.cpp
	$(CC) -o bin/$@ -c $< $(CFLAGS)

menu:
	(cd src/$@ && $(MAKE))	

.PHONY: clean mrproper

clean:
	rm bin/*.o

mrproper: clean
	rm $(EXEC)
