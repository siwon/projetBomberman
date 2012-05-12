# MakeFile ConfigFile
# Alexandre BISIAUX

CC=g++
CFLAGS=-W -Wall
LDFLAGS=
EXEC=test_ConfigFile

all: $(EXEC)

test_ConfigFile: ConfigFileManager.o test_ConfigFile.o PolyBomberException.o
	$(CC) -o $@ $^ $(LDFLAGS)

ConfigFileManager.o: ConfigFileManager.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

test_ConfigFile.o: test_ConfigFile.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

PolyBomberException.o: ../PolyBomberException.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f *.o
	rm -f *~
mrproper: clean
	rm $(EXEC)

