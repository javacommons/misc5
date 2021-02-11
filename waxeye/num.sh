#! bash -uvx
pacman -S --needed --noconfirm \
	$MINGW_PACKAGE_PREFIX-toolchain \
	$MINGW_PACKAGE_PREFIX-gtest \
	$MINGW_PACKAGE_PREFIX-openssl

waxeye -g c . -p num num.waxeye
gcc num.c num_parser.c -lwaxeye -o num
./num.exe 
