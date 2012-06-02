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
sudo make install
sudo ldconfig
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

sudo rm -rf lib/SFML2.0/CMakeCache.txt
sudo rm -rf lib/SFML2.0/CMakeFiles/*
sudo rm -rf lib/SFML2.0/Makefile
sudo rm -rf lib/SFML2.0/cmake_install.cmake
sudo rm -rf lib/SFML2.0/install_manifest.txt
sudo rm -rf lib/SFML2.0/lib/*
sudo rm -rf lib/SFML2.0/src/SFML/Audio/CMakeFiles/*
sudo rm -rf lib/SFML2.0/src/SFML/Audio/Makefile
sudo rm -rf lib/SFML2.0/src/SFML/Audio/cmake_install.cmake
sudo rm -rf lib/SFML2.0/src/SFML/CMakeFiles/*
sudo rm -rf lib/SFML2.0/src/SFML/Graphics/CMakeFiles/*
sudo rm -rf lib/SFML2.0/src/SFML/Graphics/Makefile
sudo rm -rf lib/SFML2.0/src/SFML/Graphics/cmake_install.cmake
sudo rm -rf lib/SFML2.0/src/SFML/Makefile
sudo rm -rf lib/SFML2.0/src/SFML/Network/CMakeFiles/*
sudo rm -rf lib/SFML2.0/src/SFML/Network/Makefile
sudo rm -rf lib/SFML2.0/src/SFML/Network/cmake_install.cmake
sudo rm -rf lib/SFML2.0/src/SFML/System/CMakeFiles/*
sudo rm -rf lib/SFML2.0/src/SFML/System/Makefile
sudo rm -rf lib/SFML2.0/src/SFML/System/cmake_install.cmake
sudo rm -rf lib/SFML2.0/src/SFML/Window/CMakeFiles/*
sudo rm -rf lib/SFML2.0/src/SFML/Window/Makefile
sudo rm -rf lib/SFML2.0/src/SFML/Window/cmake_install.cmake
sudo rm -rf lib/SFML2.0/src/SFML/cmake_install.cmake
sudo rm -rf lib/SFML2.0/tools/pkg-config/sfml-all.pc
sudo rm -rf lib/SFML2.0/tools/pkg-config/sfml-audio.pc
sudo rm -rf lib/SFML2.0/tools/pkg-config/sfml-graphics.pc
sudo rm -rf lib/SFML2.0/tools/pkg-config/sfml-network.pc
sudo rm -rf lib/SFML2.0/tools/pkg-config/sfml-system.pc
sudo rm -rf lib/SFML2.0/tools/pkg-config/sfml-window.pc


sudo cp /usr/local/lib/libsfml-audio.so /usr/lib
sudo cp /usr/local/lib/libsfml-audio.so.2.0 /usr/lib
sudo cp /usr/local/lib/libsfml-audio.so.2 /usr/lib

sudo cp /usr/local/lib/libsfml-graphics.so /usr/lib
sudo cp /usr/local/lib/libsfml-graphics.so.2.0 /usr/lib
sudo cp /usr/local/lib/libsfml-graphics.so.2 /usr/lib

sudo cp /usr/local/lib/libsfml-network.so /usr/lib
sudo cp /usr/local/lib/libsfml-network.so.2.0 /usr/lib
sudo cp /usr/local/lib/libsfml-network.so.2 /usr/lib

sudo cp /usr/local/lib/libsfml-system.so /usr/lib
sudo cp /usr/local/lib/libsfml-system.so.2.0 /usr/lib
sudo cp /usr/local/lib/libsfml-system.so.2 /usr/lib

sudo cp /usr/local/lib/libsfml-window.so /usr/lib
sudo cp /usr/local/lib/libsfml-window.so.2.0 /usr/lib
sudo cp /usr/local/lib/libsfml-window.so.2 /usr/lib