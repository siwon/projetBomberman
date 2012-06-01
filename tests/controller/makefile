# MakeFile Controller
# Alexandre BISIAUX

CC=g++
CFLAGS=-W -Wall -ansi -pedantic -I ../../include/
LDFLAGS=-L ../../lib/ -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network -lsfml-system -lwiic -lwiicpp
MODULES=configFile controller
EXEC=test

all: $(EXEC)

test: test_Controller.o PolyBomberException.o $(MODULES)
	$(CC) -o $@ bin/*.o $(LDFLAGS)

build:
	$(CC) -o $(EXEC) bin/*.o $(LDFLAGS)
	
test_Controller.o: test_Controller.cpp
	$(CC) -o bin/$@ -c $< $(CFLAGS)

%.o: ../../src/%.cpp
	$(CC) -o bin/$@ -c $< $(CFLAGS)

$(MODULES):
	$(MAKE) --no-print-directory -C ../../src/$@

.PHONY: clean mrproper

clean:
	-rm bin/*.o
	for i in $(MODULES); do ($(MAKE) -w -C ../../src/$$i clean); done


mrproper: clean
	-rm $(EXEC)
