# MakeFile Controller
# Alexandre BISIAUX

CC=g++
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=-lsfml-window -lsfml-graphics -lsfml-system -lwiicpp
LDPATH=/lib/
EXEC=test_Controller

all: $(EXEC)

test_Controller: test_Controller.o ControllerManager.o ConfigFileManager.o Keyboard.o Controller.o Gamepad.o PolyBomberException.o Wii.o
	$(CC) -o $@ $^ $(LDFLAGS)  -L$(LDPATH)

test_Controller.o: test_Controller.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

ControllerManager.o: ../../src/controller/ControllerManager.cpp
	$(CC) -o $@ -c $< $(CFLAGS)
	
ConfigFileManager.o: ../../src/configFile/ConfigFileManager.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

Keyboard.o: ../../src/controller/Keyboard.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

Wii.o: ../../src/controller/Wii.cpp
	$(CC) -o $@ -c $< $(CFLAGS)
	
Gamepad.o: ../../src/controller/Gamepad.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

Controller.o: ../../src/controller/Controller.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

PolyBomberException.o: ../../src/PolyBomberException.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f *.o
	rm -f *~

mrproper: clean
	rm $(EXEC)
