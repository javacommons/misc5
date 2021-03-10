
#! bash -uvx
rm -rf *.exe CMakeCache.txt CMakeFiles/ cmake_install.cmake
cmake -G "MSYS Makefiles" .
cmake --build . --config Release
