#! bash -uvx
pacman -S --needed --noconfirm \
	$MINGW_PACKAGE_PREFIX-toolchain \
    $MINGW_PACKAGE_PREFIX-boost \
	$MINGW_PACKAGE_PREFIX-gtest \
	$MINGW_PACKAGE_PREFIX-openssl \
    make

waxeye -g c . -p json json.waxeye
gcc -c json_parser.c
g++ -std=c++17 json.cpp json_parser.o -lwaxeye -o json && ./json.exe 
