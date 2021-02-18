#! bash -uvx
pacman -S --needed --noconfirm \
	$MINGW_PACKAGE_PREFIX-toolchain \
    $MINGW_PACKAGE_PREFIX-boost \
    make

g++ -std=c++17 -o demo demo.cpp && ./demo.exe
