#!/bin/bash

if [ "$CXX" = "g++" ]; then sudo apt-get install -qqy gcc g++ rpm; fi
if [ "$CXX" = "mingw" ]; then sudo apt-get install -qqy g++-mingw-w64-x86-64 nsis; fi
if [ "$CXX" = "clang++" ]; then sudo apt-get install -qqy clang rpm; fi
