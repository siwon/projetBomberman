#!/bin/sh

sudo apt-get clean
sudo apt-get remove --purge xulrunner-1.9.2
sudo apt-get install -f
make install