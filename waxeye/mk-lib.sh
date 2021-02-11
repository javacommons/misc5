#! bash -uvx
pacman -S --needed --noconfirm \
	$MINGW_PACKAGE_PREFIX-toolchain \
    make

rm -rf waxeye.tmp
cp -rp /c/Users/javac/.software/waxeye-0.8.0/src/c waxeye.tmp
cd waxeye.tmp
make
