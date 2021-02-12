#! bash -uvx
pacman -S --needed --noconfirm \
	$MINGW_PACKAGE_PREFIX-toolchain \
    $MINGW_PACKAGE_PREFIX-boost \
    $MINGW_PACKAGE_PREFIX-gc \
    make

g++ -o variant variant.cpp && ./variant.exe
