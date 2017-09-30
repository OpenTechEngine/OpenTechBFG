cd ..
rm -rf build
mkdir build
cd build
cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCEGUI=OFF -DBUNDLED_CEGUI=OFF ../
