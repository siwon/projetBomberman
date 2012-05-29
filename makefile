CC=g++
CFLAGS=-W -Wall -ansi -pedantic -I include/
LDFLAGS=-L lib/ -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network -lsfml-system -lwiic -lwiicpp
MODULES=menu sound skin configFile controller network gameInterface gameEngine
EXEC=PolyBomber

all: $(EXEC)

install:
	(./install.sh)

PolyBomber: main.o PolyBomberApp.o PolyBomberException.o $(MODULES)
	$(CC) -o $@ bin/*.o $(LDFLAGS)

build:
	$(CC) -o $(EXEC) bin/*.o $(LDFLAGS)

%.o: src/%.cpp
	$(CC) -o bin/$@ -c $< $(CFLAGS)

$(MODULES):
	$(MAKE) --no-print-directory -C src/$@

.PHONY: clean mrproper

clean:
	-rm bin/*.o
	for i in $(MODULES); do ($(MAKE) -w -C src/$$i clean); done


mrproper: clean
	-rm $(EXEC)
