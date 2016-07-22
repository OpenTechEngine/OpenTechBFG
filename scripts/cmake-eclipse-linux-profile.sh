cd ..
rm -rf build
mkdir build
cd build
cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_INSTALL_PREFIX="/opt/OpenTechEngine/OpenTechBFG" -DSDL2=OFF ../
