#! bash -uvx
pacman -S --needed --noconfirm \
	$MINGW_PACKAGE_PREFIX-toolchain \
	$MINGW_PACKAGE_PREFIX-gtest \
	$MINGW_PACKAGE_PREFIX-openssl

waxeye -g c . num.waxeye
gcc -I waxeye.tmp/include num-example.c parser.c -L waxeye.tmp -lwaxeye -o num-example
./num-example.exe 
