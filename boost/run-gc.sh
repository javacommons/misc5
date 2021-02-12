#! bash -uvx
pacman -S --needed --noconfirm \
	$MINGW_PACKAGE_PREFIX-toolchain \
    $MINGW_PACKAGE_PREFIX-boost \
    $MINGW_PACKAGE_PREFIX-gc \
    make

g++ -o gc gc.cpp -lgc -lgccpp && ./gc.exe
