#!/bin/bash

#export SDL_INCLUDE_DIR=/usr/local/opt/sdl/include
#export SDL_LIBRARY=/usr/local/opt/sdl/lib

if [ "$CXX" = "g++" ]; then cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DBUNDLED_FREETYPE=ON ../; fi

if [ "$CXX" = "clang++" ]; then cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DBUNDLED_FREETYPE=ON ../; fi

if [ "$CXX" = "mingw" ]; then echo -e 'all :\n\ttrue' > Makefile ; fi
