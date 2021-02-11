#! bash -uvx
pacman -S --needed --noconfirm \
	$MINGW_PACKAGE_PREFIX-toolchain \
    make

rm -rf waxeye.tmp
cp -rp /c/Users/javac/waxeye/src/c waxeye.tmp
cd waxeye.tmp
make
cp -rp include/* $MINGW_PREFIX/include/
cp -rp libwaxeye.a $MINGW_PREFIX/lib/
