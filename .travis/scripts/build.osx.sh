#!/bin/bash

if [ "$CXX" = "g++" ]; then cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ../; fi
if [ "$CXX" = "clang++" ]; then cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ../; fi
if [ "$CXX" = "mingw" ]; then echo -e 'all :\n\ttrue' > Makefile ; fi
