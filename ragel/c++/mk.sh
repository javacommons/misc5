#! bash -uvx
pacman -S --needed --noconfirm \
	$MINGW_PACKAGE_PREFIX-toolchain \
	$MINGW_PACKAGE_PREFIX-gtest \
	$MINGW_PACKAGE_PREFIX-openssl \
    $MINGW_PACKAGE_PREFIX-ragel

ragel -G2 -o clang.c clang.rl
gcc -o clang clang.c
