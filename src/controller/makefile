# MakeFile Controller
# Alexandre BISIAUX

CC=g++
CFLAGS=-W -Wall
LDFLAGS=-lsfml-window -lsfml-graphics -lsfml-system
EXEC=test_Controller

all: $(EXEC)

test_Controller: test_Controller.o ControllerManager.o ConfigFileManager.o Keyboard.o Controller.o Keys.o
	$(CC) -o $@ $^ $(LDFLAGS)

test_Controller.o: test_Controller.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

ControllerManager.o: ControllerManager.cpp
	$(CC) -o $@ -c $< $(CFLAGS)
	
ConfigFileManager.o: ConfigFileManager.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

Keyboard.o: Keyboard.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

Controller.o: Controller.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

Keys.o: Keys.cpp
	$(CC) -o $@ -c $< $(CFLAGS)
	
clean:
	rm -f *.o
	rm -f *~

mrproper: clean
	rm $(EXEC)
