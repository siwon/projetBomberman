CC=g++
CFLAGS=-W -Wall -ansi -pedantic -I include/
LDFLAGS=-lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network -lsfml-system -lwiicpp
EXEC=PolyBomber

all: $(EXEC)

PolyBomber: main.o PolyBomberApp.o PolyBomberException.o menu sound skin configFile controller network
	$(CC) -o $@ bin/*.o $(LDFLAGS)

build:
	$(CC) -o $(EXEC) bin/*.o $(LDFLAGS)

%.o: src/%.cpp
	$(CC) -o bin/$@ -c $< $(CFLAGS)

menu:
	(cd src/$@ && $(MAKE))

configFile:
	(cd src/$@ && $(MAKE))

skin:
	(cd src/$@ && $(MAKE))

sound:
	(cd src/$@ && $(MAKE))

controller:
	(cd src/$@ && $(MAKE))

gameInterface:
	(cd src/$@ && $(MAKE))

network:
	(cd src/$@ && $(MAKE))

gameEngine:
	(cd src/$@ && $(MAKE))

.PHONY: clean mrproper

clean:
	-rm bin/*.o

mrproper: clean
	-rm $(EXEC)
