#! bash -uvx
PACKAGE_PREFIX="${MINGW_PACKAGE_PREFIX:-mingw-w64-x86_64}"
echo $PACKAGE_PREFIX
pacman -S --needed --noconfirm \
	autoconf \
	automake-wrapper \
	make \
	libtool \
	$PACKAGE_PREFIX-toolchain \
	$PACKAGE_PREFIX-cmake \
	$PACKAGE_PREFIX-premake
