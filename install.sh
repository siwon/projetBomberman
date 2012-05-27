#ne pas faire l'installation puis pusher !!!

#!/bin/bash

#Installation des librairies
sudo apt-get update

sudo apt-get install g++

sudo apt-get install cmake
sudo apt-get install libpthread-stubs0-dev
sudo apt-get install libgl1-mesa-dev
sudo apt-get install libx11-dev
sudo apt-get install libxrandr-dev
sudo apt-get install libfreetype6-dev
sudo apt-get install libglew1.5-dev
sudo apt-get install libjpeg-dev
sudo apt-get install libsndfile1-dev
sudo apt-get install libopenal-dev

sudo apt-get install bluetooth
sudo apt-get install libbluetooth-dev

#Installation de WiiC
cd lib/WiiC/
mkdir build
cd build
sudo cmake ../src
sudo make
cp wiic/libwiic.so ../../
cp wiicpp/libwiicpp.so ../../
cd ../
sudo rm -rf build
cd ../../


#Installation de SFML2.0
cd lib/SFML2.0/

sudo cmake -G "Unix Makefiles" -D CMAKE_BUILD_TYPE=Release -D BUILD_SHARED_LIBS=TRUE .
sudo make
sudo make install
sudo cmake -G "Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug -D BUILD_SHARED_LIBS=TRUE .
sudo make
sudo make install
sudo cmake -G "Unix Makefiles" -D CMAKE_BUILD_TYPE=Release -D BUILD_SHARED_LIBS=FALSE .
sudo make
sudo make install
sudo cmake -G "Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug -D BUILD_SHARED_LIBS=FALSE .
sudo make
sudo make install
