set PATH=%PATH%;W:\programs\x64-4.8.1-release-win32-seh-rev5\mingw64\bin;C:\Program Files (x86)\CMake\bin
cd ..

del /s /q build

mkdir build

cd build

cmake -G "Eclipse CDT4 - MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_ECLIPSE_VERSION=4.4.1 ../neo

pause
