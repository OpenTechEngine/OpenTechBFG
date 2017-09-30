cd ..
rm -rf build
mkdir build
cd build
# -DCMAKE_INSTALL_PREFIX="/opt/OpenTechEngine/OpenTechBFG"
cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo ../
