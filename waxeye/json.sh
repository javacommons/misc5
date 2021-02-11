#! bash -uvx
pacman -S --needed --noconfirm \
	$MINGW_PACKAGE_PREFIX-toolchain \
	$MINGW_PACKAGE_PREFIX-gtest \
	$MINGW_PACKAGE_PREFIX-openssl

waxeye -g c . -p json json.waxeye
gcc json.c json_parser.c -lwaxeye -o json
./json.exe 
