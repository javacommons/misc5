#! bash -uvx
pacman -S --needed --noconfirm \
	$MINGW_PACKAGE_PREFIX-toolchain \
    $MINGW_PACKAGE_PREFIX-boost \
    make

g++ -o variant variant.cpp && ./variant.exe
