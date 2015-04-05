cd ..
mkdir -p build
cd build

cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=../scripts/mingw32.toolchain.cmake -DBUNDLED_FREETYPE=ON -DBUNDLED_OPENAL=ON ../
