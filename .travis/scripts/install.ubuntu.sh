#!/bin/bash

# default for the c++ image is already trusty these days
# to trusty

# if [ "$CXX" = "g++" ]; then sudo sed -i 's/precise/trusty/g' /etc/apt/sources.list; fi
# if [ "$CXX" = "mingw" ]; then sudo sed -i 's/precise/trusty/g' /etc/apt/sources.list; fi
# if [ "$CXX" = "clang++" ]; then sudo sed -i 's/precise/trusty/g' /etc/apt/sources.list; fi

# sudo apt-get update -qq
# sudo apt-get install libsdl2-dev libopenal-dev cmake

if [ "$CXX" = "g++" ]; then sudo apt-get install -qqy gcc g++ rpm; fi
if [ "$CXX" = "mingw" ]; then sudo apt-get install -qqy g++-mingw-w64-x86-64 nsis; fi
if [ "$CXX" = "clang++" ]; then sudo apt-get install -qqy clang rpm; fi
