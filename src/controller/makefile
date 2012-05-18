# MakeFile Controller
# Alexandre BISIAUX

CC=LD_LIBRARY_PATH=../../lib/ g++
CFLAGS=
LDFLAGS=-lsfml-window -lsfml-graphics -lsfml-system -lwiicpp
EXEC=test_Controller

all: $(EXEC)

test_Controller: test_Controller.o ControllerManager.o ConfigFileManager.o Keyboard.o Controller.o Gamepad.o PolyBomberException.o Wii.o
	$(CC) -o $@ $^ $(LDFLAGS)

test_Controller.o: test_Controller.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

ControllerManager.o: ControllerManager.cpp
	$(CC) -o $@ -c $< $(CFLAGS)
	
ConfigFileManager.o: ../configFile/ConfigFileManager.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

Keyboard.o: Keyboard.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

Gamepad.o: Gamepad.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

Wii.o: Wii.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

Controller.o: Controller.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

PolyBomberException.o: ../PolyBomberException.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f *.o
	rm -f *~

mrproper: clean
	rm $(EXEC)
