cd ..
rm -rf build
mkdir build
cd build

cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=mingw32.toolchain.cmake ../neo
